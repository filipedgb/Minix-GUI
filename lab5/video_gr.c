#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "vbe.h"
#include "video_gr.h"

/* Constants for VBE 0x105 mode */

/* The physical address may vary from VM to VM.
 * At one time it was 0xD0000000
 *  #define VRAM_PHYS_ADDR    0xD0000000
 * Currently on lab B107 is 0xF0000000
 * Better run my version of lab5 as follows:
 *     service run `pwd`/lab5 -args "mode 0x105"
 */
#define VRAM_PHYS_ADDR	0xF0000000
#define H_RES             1024
#define V_RES		  768
#define BITS_PER_PIXEL	  8

/* Private global variables */

static char *video_mem;		/* Process address to which VRAM is mapped */

static unsigned h_res;		/* Horizontal screen resolution in pixels */
static unsigned v_res;		/* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

void * vg_init(unsigned short mode) {
	//VBE graphics mode 105h, 1024x768@256, linear mode:

	struct reg86u r;
	r.u.w.ax = 0x4F02; // VBE call, function 02 -- set VBE mode
	r.u.w.bx = 1<<14|0x105; // set bit 14: linear framebuffer
	r.u.b.intno = 0x10;
	if( sys_int86(&r) != OK ) {
		printf("set_vbe_mode: sys_int86() failed \n");
		return NULL;
	}

	vbe_mode_info_t vmi;
	if (vbe_get_mode_info(mode, &vmi) != 0){}
	phys_bytes mem_start = vmi.PhysBasePtr;
	phys_bytes mem_limit = vmi.PhysBasePtr + vmi.XResolution * vmi.YResolution * vmi.BitsPerPixel;

	struct mem_range range;
	range.mr_base = vmi.PhysBasePtr;
	range.mr_limit = range.mr_base + vmi.XResolution * vmi.YResolution*(vmi.BitsPerPixel);
	sys_privctl(SELF, SYS_PRIV_ADD_MEM, &range);
    video_mem = vm_map_phys(SELF,(void *) range.mr_base, vmi.XResolution * vmi.YResolution * (vmi.BitsPerPixel));
//	video_mem = vm_map_phys(SELF,(void *) mem_start, mem_limit-vmi.PhysBasePtr);

	bits_per_pixel = vmi.BitsPerPixel;
	h_res = vmi.XResolution;
	v_res = vmi.YResolution;
	return NULL;
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
