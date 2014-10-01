#include <minix/drivers.h>
#include <sys/video.h>
#include <sys/mman.h>
#include <stack.h>

#include <assert.h>

#include "vt_info.h"

#include "video_txt.h"

/* Private global variables */

static char *video_mem;         /* Address to which VRAM is mapped */

static unsigned scr_width;      /* Width of screen in columns */
static unsigned scr_lines;      /* Height of screen in lines */

void vt_fill(char ch, char attr) {
	int i;
	char* current_addr = video_mem;
	for (i = 0; i < scr_width*scr_lines; i++) {
		*current_addr = ch;
		*(current_addr + sizeof(char)) = attr;
		current_addr += 2*sizeof(char);
	}
}

void vt_blank() {
	vt_fill(0x00,0x00);
}

int vt_print_char(char ch, char attr, int r, int c) {
	char* current_addr = video_mem;

	if(r < 0 || c < 0 || c > scr_width || r > scr_lines) return 1;

	current_addr += (r*scr_width + c)*2*sizeof(char);
	*current_addr = ch;
	*(current_addr + sizeof(char)) = attr;
	return 0;
}

int vt_print_string(char *str, char attr, int r, int c) {
	int row = r;
	int col = c;
	while(*str != '\0') {
		vt_print_char(*str, attr, row, col);
		if(c < scr_width) col++;
		else { //desce para a linha seguinte
			col = 0;
			row++;
		}
		str++;
	}
}

int vt_print_int(int num, char attr, int r, int c) {
	/* FUNCAO NAO TESTADA */

	int row = r;
	int col = c;
	int size = 0;
	int temp = num;

	if(num < 0) return -1;

	//count digits of number
	while(temp!=0)  {
		temp/=10;
		++size;
	}

	temp = num; //reset
	int numbers[size];

	for (i = size; i > 0; i--) { // store numbers 1 by 1 in array
		numbers[i-1] = temp % 10;
		temp /= 10;
	}

	for(i = 0; i < size; i++) { //iterate through array and print numbers
		vt_print_char(0x30 + numbers[i],attr,r,c);
	}

	return 0;

}


int vt_draw_frame(int width, int height, char attr, int r, int c) {
	int i;

	//	for(i=0; i<)

}

/*
 * THIS FUNCTION IS FINALIZED, do NOT touch it
 */

char *vt_init(vt_info_t *vi_p) {

	int r;
	struct mem_range mr;

	/* Allow memory mapping */

	mr.mr_base = (phys_bytes)(vi_p->vram_base);
	mr.mr_limit = mr.mr_base + vi_p->vram_size;

	if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
		panic("video_txt: sys_privctl (ADD_MEM) failed: %d\n", r);

	/* Map memory */

	video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vi_p->vram_size);

	if(video_mem == MAP_FAILED)
		panic("video_txt couldn't map video memory");

	/* Save text mode resolution */

	scr_lines = vi_p->scr_lines;
	scr_width = vi_p->scr_width;

	return video_mem;
}
