#include <minix/drivers.h>
#include <stdlib.h>
#include "video_gr.h"
#include <stdio.h>

#define WAIT_TIME_S 10

int main(int argc, char **argv) {
	sef_startup();
	vg_init(0x105); /* Change to video mode */
	//desenha fundo verde com uma cobra e uma maça -> snake
	vg_fill(0x16);
	vg_draw_rectangle(50,350,100,360,0x10);
	vg_draw_rectangle(100,300,110,360,0x10);
	vg_draw_rectangle(110,300,140,310,0x10);
	vg_draw_rectangle(140,300,150,360,0x10);
	vg_draw_rectangle(150,350,350,360,0x10);
	vg_draw_rectangle(370,350,380,360,0x24);
	//

	//	vg_draw_line(10,50,400,50,0x23);
	sleep(WAIT_TIME_S); /* for WAIT_TIME_S (5) seconds */

	vg_exit(); /* Return to text mode */


  return 0;

}
