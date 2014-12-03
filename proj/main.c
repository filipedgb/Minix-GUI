#include "test5.h"
#include "pixmap.c"

#include <minix/drivers.h>


//int main(int argc, char **argv) {
//	sef_startup();
//
//	//test_init(0x105,3);
//
//	test_square(15,70,400,0x16);
//
//	//test_line(0,0,100,0,0x16); //horizontal
//	//test_line(0,0,0,100,0x16); //vertical
//	//test_line(0,0,100,100,0x16); // i > f
//	//test_line(100,10,70,100,0x16); // yi > yf
//	test_line(100,10,10,100,0x16); // xi > xf
//	//test_line(50,5,0,0,0x16); // xi > xf, yi > yf
//
//	//test_xpm(500,200,penguin);
//
//	//test_move(100, 100, penguin, 0, 3, 0);
//
//	return 0;
//
//}

static int proc_args(int argc, char *argv[]);
static unsigned long parse_ulong(char *str, int base);
static long parse_long(char *str, int base);
static void print_usage(char *argv[]);

int main(int argc, char **argv) {
	/* Initialize service */
	sef_startup();



//	test_xpm(100,100,penguin);

	test_move(100,100,penguin,0,100,30) ;

}



