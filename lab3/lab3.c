#include "headers.h"
#include "test3.h"

#include <minix/drivers.h>


static int proc_args(int argc, char *argv[]);
static unsigned long parse_ulong(char *str, int base);
static long parse_long(char *str, int base);
static void print_usage(char *argv[]);

int main(int argc, char **argv) {

	/* Enable IO-sensitive operations for ourselves */
	//sys_iopenable(SELF);


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
	 "\t service run %s -args \"scan <0 for C code, otherwise for Assembly>\" \n"
	 "\t service run %s -args \"leds <decimal number> <array of decimal numbers>\" \n"
	 "\t service run %s -args \"timescan <decimal number>\" \n",
	 argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char *argv[]) {

  unsigned long temp;
  unsigned short* temp_array;
  unsigned long array_value;

  /* check the function to test: if the first characters match, accept it */
  if (strncmp(argv[1], "scan", strlen("scan")) == 0) {
	  if( argc != 3 ) {
		  printf("Wrong no of arguments for kbd_test_scan() \n");
		  return 1;
	  }
	  if((temp = parse_ulong(argv[2], 10)) == ULONG_MAX ) return 1;
	  printf("Called kbd_test_scan(%lu) \n", temp);
	  kbd_test_scan((unsigned short)temp);
	  return 0;
  }

  else if (strncmp(argv[1], "leds", strlen("leds")) == 0) {
	  if( argc < 4) {
		  printf("Wrong no of arguments for kbd_test_leds() \n");
		  return 1;
	  }
	  if((temp = parse_ulong(argv[2], 10)) == ULONG_MAX ) return 1;

	  /* Verifica se o valor do 1º argumento (nº de toggles do array) é igual ao tamanho do array passado */
	  if(temp != argc-3){
		  printf("Your array should be the size of the 1st parameter passed\n");
		  return 1;
	  }

	  /* Preenche um array de toggles e verifica se são válidos (entre 0 e 2) */
	  temp_array = (unsigned short*)malloc( temp*sizeof(unsigned short)); // allocate memory for leds array
	  int i;
	  for(i=0; i < temp; i++) {
		  if((array_value = parse_ulong(argv[i+3], 10)) == ULONG_MAX ) return 1;
		  if(array_value > 2 || array_value < 0) printf("\nERROR: Leds values must range from 0 to 2\n");
		  else temp_array[i] = (unsigned short) array_value ;
	  }

	  /* Imprime e chama a função */
	  printf("Called kbd_test_leds(%lu", temp);
	  for(i=0; i < temp; i++) printf(" ,LED %lu", temp_array[i]);
	  printf(")\n");

	  kbd_test_leds(temp,temp_array);
	  return 0;
  }

  else if (strncmp(argv[1], "timescan", strlen("timescan")) == 0) {
	  if( argc != 3 ) {
		  printf("Wrong no of arguments for scantime() \n");
	  	  return 1;
	  }
	  if((temp = parse_ulong(argv[2], 10)) == ULONG_MAX ) return 1;
	  printf("Called timescan(%lu) \n", temp);
	  kbd_test_timed_scan((unsigned short)temp);
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

