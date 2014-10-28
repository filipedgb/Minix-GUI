#include "test3.h"
#include <minix/syslib.h>
#include <minix/drivers.h>
#include "headers.h"
#include "i8254.h"
#include "timer.h"

int kbd_test_scan(unsigned short ass) {
	timer_flag = 0;

	if(ass == 0) assembly_flag = 0;
	else {
		printf("Assembly code chosen.\n");
		setAssemblyFlag();
	}

	receiver_loop();

	return 0;

}

int kbd_test_leds(unsigned short n, unsigned short *leds) {
	// 0 - scroll lock, 1 - numeric lock,  2 - caps lock

	// Input Verification
	int i;

	/* Imprime e verifica se os valores dos leds para toggle sao todos validos */
	for(i=0; i < n; i++) {
		printf("LED: %lu \n",leds[i]);
		if( leds[i] > 2 ||  leds[i] < 0){
			printf("\nERROR: Leds values must range from 0 to 2\n");
			return 1;
		}
	}

	// FUNCAO EM SI

	int leds_argument_cmd = 0; // command to be sent
	leds_state = malloc(3*sizeof(int)); // array with the current states of each led
	for(i=0; i < 3; i++) leds_state[i] = 0; // array initalization
	keyboard_subscribe_int();


	for(i=0; i < n; i++) {

		/* bit masks */
		if(leds_state[leds[i]] == 1) leds_argument_cmd &= (~(1 << leds[i])); //if the state is ON, we have to set the bit to 0 with a mask
		else leds_argument_cmd |= (1 << leds[i]); // if not , we want to set the bit to 1 with another mask

		printf("ARGUMENT: 0x%x \n",leds_argument_cmd); // prints the argument so we can see the command was masked successfully

		if (issue_command(0xED,leds_argument_cmd) != 0) printf("\nerro 1\n");
		else {
			leds_state[leds[i]] = !leds_state[leds[i]]; // toggle led state (in the array of states) of the led indicated in leds array
		}

		//tickdelay(micros_to_ticks(DELAY_US));
		sleep(2);
	}

	issue_command(0xF6,-1);
	keyboard_unsubscribe_int();
	return 0;

}

int kbd_test_timed_scan(unsigned short n) {
	setTimerFlag();
	setTime(n);
	receiver_loop();
}
