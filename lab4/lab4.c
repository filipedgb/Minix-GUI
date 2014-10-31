#include "lab4.h"
#include "test4.h"

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
  printf("Usage: one of the following:\n\n"
	 "service run %s -args \"packets <decimal number>\" \n"
	 "service run %s -args \"async <decimal number>\" \n"
	 "service run %s -args \"config\" \n"
	 "service run %s -args \"gesture <decimal number> <positive decimal number>\" \n\n",
	 argv[0], argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char *argv[]) {

  unsigned long temp,temp2;

  /* check the function to test: if the first characters match, accept it */
  if (strncmp(argv[1], "packets", strlen("packets")) == 0) {
	  if( argc != 3 ) {
		  printf("Wrong no of arguments for test_packet() \n");
		  return 1;
	  }
	  if((temp = parse_ulong(argv[2], 10)) == ULONG_MAX ) return 1;
	  printf("Called test_packet(%lu) \n", temp);
	  test_packet((unsigned short)temp);
	  return 0;
  }

  else if (strncmp(argv[1], "async", strlen("async")) == 0) {
	  if( argc != 3) {
		  printf("Wrong no of arguments for test_async() \n");
		  return 1;
	  }
	  if((temp = parse_ulong(argv[2], 10)) == ULONG_MAX ) return 1;
	  printf("Called test_async(%lu)", temp);
	  test_async((unsigned short)temp);
	  return 0;
  }

  else if (strncmp(argv[1], "config", strlen("config")) == 0) {
	  if( argc != 2 ) {
		  printf("Wrong no of arguments for test_config() \n");
	  	  return 1;
	  }
	  if((temp = parse_ulong(argv[2], 10)) == ULONG_MAX ) return 1;
	  printf("Called test_config(void) \n", temp);
	  test_config();
	  return 0;
  }

  else if (strncmp(argv[1], "gesture", strlen("gesture")) == 0) {
	  if( argc != 3 ) {
		  printf("Wrong no of arguments for test_gesture() \n");
	  	  return 1;
	  }
	  if((temp = parse_ulong(argv[2], 10)) == ULONG_MAX ) return 1;
	  if((temp2 = parse_ulong(argv[3], 10)) == ULONG_MAX ) return 1;
	  printf("Called test_gesture(%lu, %lu) \n",temp,temp2);
	  test_gesture((short) temp, (unsigned short) temp2);
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

