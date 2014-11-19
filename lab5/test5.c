#include "test5.h"
#include "keyboard.h"
#include "read_xpm.h"

void *test_init(unsigned short mode, unsigned short delay) {
	vg_init(mode);
	sleep(delay);
	vg_exit();

}


int test_square(unsigned short x, unsigned short y, unsigned short size, unsigned long color) {
	int shift = keyboard_subscribe_int();

	vg_init(0x105);
	draw_rectangle(x,y,size,size,color);

	if(receiver_loop(shift)) {
		vg_exit();
		keyboard_unsubscribe_int();
	}

	return 0;
}

int test_line(unsigned short xi, unsigned short yi,
		unsigned short xf, unsigned short yf, unsigned long color) {

	int shift = keyboard_subscribe_int();

	vg_init(0x105);

	draw_line(xi,yi,xf,yf,color);

	if(receiver_loop(shift)) {
		vg_exit();
		keyboard_unsubscribe_int();
	}

	return 0;
}

int test_xpm(unsigned short xi, unsigned short yi, char *xpm[]) {


	int width, height;
	char *map;
	// get the pix map from the XPM
	map = read_xpm(xpm, &width, &height);
	// copy it to graphics memory

	vg_init(0x105);

	draw_map(xi,yi,width,height,map);

	sleep(2);

	vg_exit();

	return 0;

}

int test_move(unsigned short xi, unsigned short yi, char *xpm[],
		unsigned short hor, short delta, unsigned short time) {

	/* To be completed */

}

