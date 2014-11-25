#include "test5.h"
#include "keyboard.h"
#include "read_xpm.h"

#include "sprite.h"

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

	vg_init(0x105);

	draw_sprite(xi, yi, xpm);

	sleep(2);

	vg_exit();

	return 0;

}

int test_move(unsigned short xi, unsigned short yi, char *xpm[],
		unsigned short hor, short delta, unsigned short time) {

	vg_init(0x105);

	int i = 0;
	for (i; i < delta; i++) {
		if (hor == 0) {
			draw_sprite(xi, yi + i, xpm); //vertical

		}
		else {
			draw_sprite(xi + i, yi, xpm); //horizontal
		}
	}

	vg_exit();

	return 0;
}

int test_controller() {
	return 0;
}


