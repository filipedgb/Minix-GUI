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
	// Input Verification
	int i;
	for(i=0; i < n; i++) { /* Imprime e verifica se os valores dos leds para toggle sao todos validos */
		printf("LED: %lu \n",leds[i]);
		if( leds[i] > 2 ||  leds[i] < 0){
			printf("\nERROR: Leds values must range from 0 to 2\n");
			return 1;
		}
	}

	keyboard_subscribe_int();
	process_leds(n,leds);
	reset_leds();
	keyboard_unsubscribe_int();
	return 0;

}

int kbd_test_timed_scan(unsigned short n) {
	setTimerFlag();
	setTime(n);
	receiver_loop();
}
