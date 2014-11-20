#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>
#include "vbe.h"


/* Constants for VBE 0x105 mode */

/* The physical address may vary from VM to VM.
 * At one time it was 0xD0000000
 *  #define VRAM_PHYS_ADDR    0xD0000000 
 * Currently on lab I304 is 0xF0000000
 * Better run my version of lab2 as follows:
 *     service run `pwd`/lab2 -args "mode 0x105"
 */
#define VRAM_PHYS_ADDR	0xE0000000
#define H_RES             1024
#define V_RES		  768
#define BITS_PER_PIXEL	  8

/* Private global variables */

static char *video_mem;		/* Process address to which VRAM is mapped */

static unsigned h_res;		/* Horizontal screen resolution in pixels */
static unsigned v_res;		/* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

void * vg_init(unsigned short mode) {

	struct reg86u r;
	r.u.w.ax = 0x4F02;
	r.u.w.bx = 1<<14|0x105;
	r.u.b.intno = 0x10;
	if( sys_int86(&r) != OK ) {
		printf("set_vbe_mode: sys_int86() failed \n");
		return NULL;
	}

	/* O RESTO DESTA FUN��O � PRECISO REFORMULAR  */
	vbe_mode_info_t vmi;
	if (vbe_get_mode_info(mode, &vmi) != 0){}
	phys_bytes mem_start = vmi.PhysBasePtr;
	phys_bytes mem_limit = vmi.PhysBasePtr + vmi.XResolution * vmi.YResolution * vmi.BitsPerPixel;

	struct mem_range range;
	range.mr_base = vmi.PhysBasePtr;
	range.mr_limit = range.mr_base + vmi.XResolution * vmi.YResolution*(vmi.BitsPerPixel);
	sys_privctl(SELF, SYS_PRIV_ADD_MEM, &range);
	video_mem = vm_map_phys(SELF,(void *) range.mr_base, vmi.XResolution * vmi.YResolution * (vmi.BitsPerPixel));

	bits_per_pixel = vmi.BitsPerPixel;
	h_res = vmi.XResolution;
	v_res = vmi.YResolution;
	return NULL;
}

int vg_set_pixel(unsigned long x, unsigned long y, unsigned long color) {
	*(video_mem + x + y*h_res) = color;
	return 0;
}

//Used for draw_rectangle
int draw_line(unsigned short xi, unsigned short yi, unsigned short xf, unsigned short yf, unsigned long color);

int draw_rectangle(unsigned short x, unsigned short y, unsigned short width,unsigned short height, unsigned long color) {
	int i;

	if(x < 0 || y < 0 || x+width > H_RES || y+height > V_RES) {
		printf("Error: out of the screen limits\n");
		return 1;
	}

	//Horizontal - cima
	draw_line(x,y,x + width,y,color);
	//baixo
	draw_line(x,y + height,x + width,y + height,color);

	//Vertical - esquerda
	draw_line(x,y,x,y + height,color);
	//direita
	draw_line(x + width,y,x + width,y + height,color);


	return 0;
}

int draw_line(unsigned short xi, unsigned short yi, unsigned short xf, unsigned short yf, unsigned long color) {

	int dx, dy;
	int sx, sy;
	int error, error2;

	if (xi < 0 || yi < 0 || xf < 0 || yf < 0) {
		printf("Error: out of the screen limits\n");
		return 1;
	}

	dx = abs(xf - xi);
	sx = xi < xf ? 1 : -1;

	dy = abs(yf - yi);
	sy = yi < yf ? 1 : -1;

	error = (dx > dy ? dx : -dy) / 2;

	while(1) {

		vg_set_pixel(xi,yi,color);

		if (xi == xf && yi == yf) break;

		error2 = error;
	    if (error2 > -dx) {
	    	error -= dy;
	    	xi += sx;
	    }
	    if (error2 < dy) {
	    	error += dx;
	    	yi += sy;
	    }
	}

	return 0;
}

int draw_map(unsigned short xi, unsigned short yi,  int n_columns,int n_rows, char * pixmap) {

	int i, k;

	unsigned video_mem_rowsize = H_RES*(BITS_PER_PIXEL/8);

	unsigned xpm_row_size = n_columns*(BITS_PER_PIXEL/8);

	for(i = 0; i < n_rows ; i++){
		void* dest = video_mem +  video_mem_rowsize*(yi+i) + xi*(BITS_PER_PIXEL/8);
		void* src = pixmap + xpm_row_size*i;
		memcpy(dest,src,xpm_row_size);

	}
	return 0;

}


int vg_exit() {
	struct reg86u reg86;

	reg86.u.b.intno = 0x10; /* BIOS video services */

	reg86.u.b.ah = 0x00;    /* Set Video Mode function */
	reg86.u.b.al = 0x03;    /* 80x25 text mode*/

	if( sys_int86(&reg86) != OK ) {
		printf("\tvg_exit(): sys_int86() failed \n");
		return 1;
	} else
		return 0;
}
