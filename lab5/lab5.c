#include "test5.h"
#include "pixmap.c"

#include <minix/drivers.h>

/*
int main(int argc, char **argv) {
	sef_startup();

	//test_init(0x105,3);

	//test_square(15,70,400,0x16);

	//test_line(0,0,100,0,0x16); //horizontal
	//test_line(0,0,0,100,0x16); //vertical
	//test_line(0,0,100,100,0x16); // i > f
	//test_line(100,10,70,100,0x16); // yi > yf
	//test_line(100,10,10,100,0x16); // xi > xf
	//test_line(50,5,0,0,0x16); // xi > xf, yi > yf

	//test_xpm(500,200,penguin);

	test_move(100, 100, penguin, 0, 3, 0);

	return 0;

}*/

static int proc_args(int argc, char *argv[]);
static unsigned long parse_ulong(char *str, int base);
static long parse_long(char *str, int base);
static void print_usage(char *argv[]);

int main(int argc, char **argv) {
	/* Initialize service */
	sef_startup();
	if ( argc == 1 ) {
		print_usage(argv);
		return 0;
	} else {
		proc_args(argc, argv);
	}
	return 0;

}


/*
 * SCAFFOLDING TEST CODE BASED ON THE CODE PROVIDED FOR LAB1
 */


static void print_usage(char *argv[]) {
	printf("Usage: one of the following:\n\n"
			"service run %s -args \"init <int> <int>\" \n"
			"service run %s -args \"square <int> <int> <int> <hex>\" \n"
			"service run %s -args \"line <int> <int> <int> <int> <hex>\" \n"
			"service run %s -args \"xpm <int> <int> <char>\" \n"
			"service run %s -args \"move <int> <int> <char> <int> <int> <int>\" \n"
			"service run %s -args \"controller\" \n\n",
			argv[0], argv[0], argv[0], argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char *argv[]) {

	unsigned long temp,temp2,temp3,temp4,temp5,temp6;

	/* check the function to test: if the first characters match, accept it */
	if (strncmp(argv[1], "init", strlen("init")) == 0) {
		if( argc != 4 ) {
			printf("Wrong no of arguments for test_init()\n");
			return 1;
		}
		if((temp = parse_ulong(argv[2], 10)) == ULONG_MAX ) return 1;
		if((temp2 = parse_ulong(argv[3], 10)) == ULONG_MAX ) return 1;

		printf("Called test_init(%lu,%lu)\n", temp,temp2);
		test_init((unsigned short)temp,(unsigned short)temp2);
		return 0;
	}

	else if (strncmp(argv[1], "square", strlen("square")) == 0) {
		if( argc != 6) {
			printf("Wrong no of arguments for test_square() \n");
			return 1;
		}
		if((temp = parse_ulong(argv[2], 10)) == ULONG_MAX ) return 1;
		if((temp2 = parse_ulong(argv[3], 10)) == ULONG_MAX ) return 1;
		if((temp3 = parse_ulong(argv[4], 10)) == ULONG_MAX ) return 1;
		if((temp4 = parse_ulong(argv[5], 10)) == ULONG_MAX ) return 1;


		printf("Called test_square(%lu,%lu,%lu,%lu)\n", temp,temp2,temp3,temp4);
		test_square((unsigned short)temp,(unsigned short)temp2,(unsigned short)temp3,(unsigned short)temp4);
		return 0;
	}

	else if (strncmp(argv[1], "line", strlen("line")) == 0) {
		if( argc != 7 ) {
			printf("Wrong no of arguments for test_line() \n");
			return 1;
		}
		if((temp = parse_ulong(argv[2], 10)) == ULONG_MAX ) return 1;
		if((temp2 = parse_ulong(argv[3], 10)) == ULONG_MAX ) return 1;
		if((temp3 = parse_ulong(argv[4], 10)) == ULONG_MAX ) return 1;
		if((temp4 = parse_ulong(argv[5], 10)) == ULONG_MAX ) return 1;
		if((temp5 = parse_ulong(argv[6], 10)) == ULONG_MAX ) return 1;


		printf("Called test_line(%lu,%lu,%lu,%lu)\n", temp,temp2,temp3,temp4);
		test_line((unsigned short)temp,(unsigned short)temp2,(unsigned short)temp3,(unsigned short)temp4,(unsigned short)temp5);
		return 0;
	}

	else if (strncmp(argv[1], "xpm", strlen("xpm")) == 0) {
		if( argc != 4 ) {
			printf("Wrong no of arguments for test_xpm() \n");
			return 1;
		}
		if((temp = parse_ulong(argv[2], 10)) == ULONG_MAX ) return 1;
		if((temp2 = parse_ulong(argv[3], 10)) == ULONG_MAX ) return 1;

		printf("Called test_xpm(%lu, %lu, penguin[]) \n",temp,temp2);
		test_xpm((short) temp, (unsigned short) temp2,penguin);
		return 0;
	}

	else if (strncmp(argv[1], "move", strlen("move")) == 0) {
		if( argc != 7 ) {
			printf("Wrong no of arguments for test_move() \n");
			return 1;
		}
		if((temp = parse_ulong(argv[2], 10)) == ULONG_MAX ) return 1;
		if((temp2 = parse_ulong(argv[3], 10)) == ULONG_MAX ) return 1;
		if((temp3 = parse_ulong(argv[4], 10)) == ULONG_MAX ) return 1;
		if((temp4 = parse_ulong(argv[5], 10)) == ULONG_MAX ) return 1;
		if((temp5 = parse_ulong(argv[6], 10)) == ULONG_MAX ) return 1;

		printf("Called test_move(%lu, %lu, penguin[],%lu,%lu,%lu)\n",temp,temp2,temp3,temp4,temp5);
		test_move((unsigned short) temp, (unsigned short) temp2,penguin,(unsigned short) temp3,(unsigned short) temp4,(unsigned short) temp5);

		return 0;
	}

	else if (strncmp(argv[1], "controller", strlen("controller")) == 0) {
		if( argc != 2 ) {
			printf("Wrong no of arguments for test_controller() \n");
			return 1;
		}

		printf("Called test_controller() \n");
		test_controller();
		return 0;
	}


	else {
		printf("Non valid function \"%s\" to test\n", argv[1]);
		return 1;
	}
}

/* THE FOLLOWING FUNCTIONS WERE COPIED FROM LAB1 PROVIDED CODE */

static unsigned long parse_ulong(char *str, int base) {
	char *endptr;
	unsigned long val;

	val = strtoul(str, &endptr, base);

	if ((errno == ERANGE && val == ULONG_MAX )
			|| (errno != 0 && val == 0)) {
		perror("strtol");
		return ULONG_MAX;
	}

	if (endptr == str) {
		printf("Parse_ulong: no digits were found in %s \n", str);
		return ULONG_MAX;
	}

	/* Successful conversion */
	return val;
}

static long parse_long(char *str, int base) {
	char *endptr;
	unsigned long val;

	val = strtol(str, &endptr, base);

	if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
			|| (errno != 0 && val == 0)) {
		perror("strtol");
		return LONG_MAX;
	}

	if (endptr == str) {
		printf("parse_long: no digits were found in %s \n", str);
		return LONG_MAX;
	}

	/* Successful conversion */
	return val;
}



