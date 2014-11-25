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

	int width, height;
	char *map_sprite, *map_here;

	map_sprite = initialize_sprite(xpm);
	//map_here = read_xpm(xpm, &width, &height);

	//map_sprite =/= map_here pq??

	if(map_sprite == map_here) printf("Okay"); else printf("Not Okay");sleep(1);

	vg_init(0x105);

	draw_map(xi,yi,width,height,map_sprite);

	sleep(2);

	vg_exit();

	return 0;

}

int test_move(unsigned short xi, unsigned short yi, char *xpm[],
		unsigned short hor, short delta, unsigned short time) {

	int shift = keyboard_subscribe_int();

	vg_init(0x105);

	int i = 0;
	for (i; i < delta; i++) {
		if (hor == 0) test_xpm(xi, yi + i, xpm); //vertical
		else test_xpm(xi + i, yi, xpm); //horizontal
	}

	if(receiver_loop(shift)) {
			vg_exit();
			keyboard_unsubscribe_int();
		}

	return 0;
}

int test_controller() {
	return 0;
}


