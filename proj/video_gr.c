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


unsigned getHRES() {
	return h_res;
}


unsigned getVRES() {
	return v_res;
}


void * vg_init(unsigned short mode) {

	struct reg86u r;
	r.u.w.ax = 0x4F02;
	r.u.w.bx = 1<<14|0x105;
	r.u.b.intno = 0x10;
	if( sys_int86(&r) != OK ) {
		printf("set_vbe_mode: sys_int86() failed \n");
		return NULL;
	}

	/* calls vbe_get_mode_info to fill vbe_info struct*/
	vbe_mode_info_t vbe_info;
	if (vbe_get_mode_info(mode, &vbe_info) != 0){
		printf("Error reading vbe mode info\n");
	}

	//Store values in private global variables

	h_res = vbe_info.XResolution;
	v_res = vbe_info.YResolution;
	bits_per_pixel = vbe_info.BitsPerPixel;


	/* CODE BASED ON LAB1 VT_INIT TO GET VIDEO_MEM ADDRESS */

	struct mem_range mem_range;

	/* Allow memory mapping */
	mem_range.mr_base = vbe_info.PhysBasePtr;
	mem_range.mr_limit = mem_range.mr_base + h_res*v_res*bits_per_pixel;

	if( sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mem_range) != OK) {
		panic("video_gr: sys_privctl (ADD_MEM) failed: %d\n", r);
	}

	/* Map memory */
	video_mem = vm_map_phys(SELF,(void *) mem_range.mr_base, h_res*v_res*bits_per_pixel);
	if(video_mem == MAP_FAILED) panic("video_gr couldn't map video memory");

	return NULL;
}

int vg_set_pixel(unsigned long x, unsigned long y, unsigned long color) {
	*(video_mem + x + y*h_res) = color;
	return 0;
}


int vg_fill(unsigned long color) {
	int i, success;

	for(i = 0; i < h_res*v_res; i++){
		*(video_mem + i ) = color;
	}

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

	draw_line(x,y,x + width,y,color); //cima
	draw_line(x,y + height,x + width,y + height,color); //baixo
	draw_line(x,y,x,y + height,color); //esquerda
	draw_line(x + width,y,x + width,y + height,color); //direita

	return 0;
}


int draw_solid_rectangle(unsigned short x, unsigned short y, unsigned short width,unsigned short height, unsigned long color ) {
	if(x < 0 || y < 0 || x+width > H_RES || y+height > V_RES) {
		printf("Error: out of the screen limits\n");
		return 1;
	}

	int i = 0;

	for (; i < height; i++) {
		draw_line(x,y+i,x+width,y+i,color);
	}


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

void vt_blank() {

	int row = 0; int column = 0;
	int i = 0;
	for (i; i < H_RES*V_RES; i++) {
		if (column == H_RES) {column = 0; row++;}
		vg_set_pixel(column, row, 0x00);
		column++;
	}
}

void display_VBE_controller_info() {

	VbeInfoBlock_t vbe_info;
	char* apontador;

	printf("size: %d", sizeof(VbeInfoBlock_t));


	if (vbe_get_info(&vbe_info,apontador) != 0){
		printf("Error reading vbe info\n");
	}

	int capabilities = (int) vbe_info.Capabilities;

	if(capabilities & 0x01) printf("DAC width is switchable to 8 bits per primary color\n");
	else printf("DAC is fixed width, with 6 bits per primary color\n");

	if(capabilities >> 1 & 0x01) printf("Controller is not VGA compatible\n");
	else printf("Controller is VGA compatible\n");

	if(capabilities >> 2 & 0x01 ) printf(" When programming large blocks of information to the RAMDAC,use the blank bit in Function 09h \n");
	else printf("Normal RAMDAC operation\n");

	printf("\nSIZE OF VRAM MEMORY: %lu",vbe_info.TotalMemory);

	//	/*MODES*/
	//
	//	int segment = VideoModePtr[1] << 4;
	//	int offset = VideoModePtr[0];
	//
	//	int resultado = segment + offset;
	//
	//	char* enderecofinal = apontador+resultado;
	//
	//
	//	//Usar endereço final para fazer print dos modes aqui
	//
	//	return;
	//

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
