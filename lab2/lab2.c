#include "timer.h"
#include "i8254.h"

#include <minix/drivers.h>


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
  printf("Usage: one of the following:\n"
	 "\t service run %s -args \"config <decimal number>\" \n"
	 "\t service run %s -args \"square <decimal number>\" \n"
	 "\t service run %s -args \"int <decimal number>\" \n",
	 argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char *argv[]) {

  unsigned long timer;

  /* check the function to test: if the first characters match, accept it */
  if (strncmp(argv[1], "config", strlen("config")) == 0) {
	  if( argc != 3 ) {
		  printf("Wrong no of arguments for timer_test_config() \n");
		  return 1;
	  }
	  if((timer = parse_ulong(argv[2], 10)) == ULONG_MAX ) return 1;
	  printf("Called timer_test_config(%lu) \n", timer);
	  timer_test_config(timer);
	  return 0;
  } else if (strncmp(argv[1], "square", strlen("square")) == 0) {
	  if( argc != 3 ) {
		  printf("Wrong no of arguments for timer_test_square() \n");
		  return 1;
	  }
	  if((timer = parse_ulong(argv[2], 10)) == ULONG_MAX ) return 1;
	  printf("Called timer_test_square(%lu) \n", timer);
	  timer_test_square(timer);
	  return 0;
  } else if (strncmp(argv[1], "int", strlen("int")) == 0) {
	  if( argc != 3 ) {
		  printf("Wrong no of arguments for timer_test_int() \n");
	  	  return 1;
	  }
	  if((timer = parse_ulong(argv[2], 10)) == ULONG_MAX ) return 1;
	  printf("Called timer_test_int(%lu) \n", timer);
	  timer_test_square(timer);
	  return 0;
  }
  else {
	  printf("video_txt: non valid function \"%s\" to test\n", argv[1]);
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
	  printf("video_txt: parse_ulong: no digits were found in %s \n", str);
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
	  printf("video_txt: parse_long: no digits were found in %s \n", str);
	  return LONG_MAX;
  }

  /* Successful conversion */
  return val;
}
