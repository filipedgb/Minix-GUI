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

	//test_square(500,200,100,0x16);

	test_line(-50,50,150,250,0x16);

	//test_xpm(500,200,penguin);

	return 0;

}
