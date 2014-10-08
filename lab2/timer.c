#include <minix/syslib.h>
#include <minix/drivers.h>
#include "i8254.h"

int timer_set_square(unsigned long timer, unsigned long freq) {

	return 1;
}

int timer_subscribe_int(void ) {

	return 1;
}

int timer_unsubscribe_int() {

	return 1;
}

void timer_int_handler() {

}

int timer_get_conf(unsigned long timer, unsigned char *st) {
	port_t control_reg = TIMER_CTRL;

	unsigned long temp;

	//Set readback command with correct bits
	char read_back_command = 0 | TIMER_RB_SEL(timer)| TIMER_RB_COUNT_ | BIT(6) | BIT(7);

	if(sys_outb(control_reg, read_back_command) != OK)  {
		return 1;
	}

	if(sys_inb(TIMER_0+timer, &temp ) != OK)  {
		return 1;
	}

	*st = (char) temp;

	return 0;

}

int timer_display_conf(unsigned char conf) {
	printf("timer config: %c", conf);
	return 1;
}

int timer_test_square(unsigned long freq) {
	
	return 1;
}

int timer_test_int(unsigned long time) {
	
	return 1;
}

int timer_test_config(unsigned long timer) {
	char config;
	if(!timer_get_conf(timer,&config)) {
		printf("TESTE");
		return timer_display_conf(config);
	}
	else return 1;
}
