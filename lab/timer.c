#include <minix/syslib.h>
#include <minix/drivers.h>
#include "i8254.h"

int timer_set_square(unsigned long timer, unsigned long freq) {
	port_t control_reg = TIMER_CTRL;

	char temp;
	char* timer_ptr;
	timer_get_conf(timer_ptr,&temp);

	char control_word = temp | BIT(4) | BIT(5) | TIMER_RB_SEL(timer);

	if(sys_outb(control_reg, control_word) != OK)  {
		return 1;
	}

	int div = freq*TIMER_FREQ;

	if(timer == 0) timer = TIMER_0;
	else if (timer == 1) timer = TIMER_1;
	else timer = TIMER_2;

	if(sys_outb(timer, div) != OK)  {  // Send LSB
			return 1;
	}

	if(sys_outb(timer, div >> 8) != OK)  {  // Send MSB
			return 1;
	}

	return 0;
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
	if(conf >> 7 && 0x01) printf("Timer output: 1 \n");
	else printf("Timer output: 0 \n");

	if(conf >> 6 && 0x01 ) printf("Timer null count: 1 \n");
	else printf("Timer null count: 0 \n");

	if((conf >> 5 && 0x01 ) && (conf >> 4 && 0x01 ))  printf("Type of access: LSB followed by MSB \n");
	else if (conf >> 5 && 0x01 ) printf("Type of access: MSB \n");
	else printf("Type of access: LSB \n");

	if((conf >> 5 && 0x01 ) && (conf >> 4 && 0x01 ))  printf("Type of access: LSB followed by MSB \n");
	else if (conf >> 5 && 0x01 ) printf("Type of access: MSB \n");
	else printf("Type of access: LSB \n");


	if(conf && 0x01 ) printf("Counting mode: Binary \n");
	else printf("Counting mode: BCD \n");

	return 1;
}

int timer_test_square(unsigned long freq) {
	timer_set_square(2,freq);
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
