#include <minix/drivers.h>
#include <stdlib.h>
#include "video_gr.h"
#include <stdio.h>

#include "pixmap.c"

#include "test5.h"

#define WAIT_TIME_S 10

int main(int argc, char **argv) {
	sef_startup();

	//test_init(0x105,3);

	//test_square(0,0,100,0x16);

	//test_line(0,0,100,100,0x16); // i > f
	//test_line(100,10,70,100,0x16); // yi > yf
	//test_line(100,10,10,100,0x16); // xi > xf
	//test_line(50,5,0,0,0x16); // xi > xf, yi > yf

	//test_xpm(500,200,penguin);

	return 0;

}
