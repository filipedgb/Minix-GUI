#include <minix/syslib.h>
#include <minix/drivers.h>
#include "i8254.h"

static int counter = 0;
static int hook_id = 0;

int timer_set_square(unsigned long timer, unsigned long freq) {
	port_t control_reg = TIMER_CTRL;
	int div = freq*TIMER_FREQ;
	char old_config;

	// "requires you to read the Timer 0 configuration before you change it." //
	timer_get_conf(timer,&old_config);

	// changing type of access and timer bits only. Square wave mode is default and as said "do not change the 4 least significant bits"
	char control_word = old_config | BIT(4) | BIT(5) | TIMER_RB_SEL(timer);
	if(sys_outb(control_reg, control_word) != OK) return 1;

	timer = TIMER_0 + timer; //doing so will convert the timer number (0 to 2) to its corresponding address (0x40 to 0x42)

	if(sys_outb(timer, div) != OK) return 1; //send LSB
	if(sys_outb(timer, div >> 8) != OK) return 1; //send MSB

	return 0;
}

int timer_subscribe_int(void ) {
	int temp = hook_id; //integer between 0 and 31
	sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE,&hook_id); // returns a hook id that you can then use to enable and disable irqs.
	sys_irqenable(&hook_id);
	return temp;
}

int timer_unsubscribe_int() {
	if (sys_irqrmpolicy(&hook_id)!= OK) return 1;
	return 0;
}

void timer_int_handler() {
	counter++;
}

int timer_get_conf(unsigned long timer, unsigned char *st) {
	port_t control_reg = TIMER_CTRL;
	unsigned long temp;

	//Set readback command with correct bits
	char read_back_command = 0 | TIMER_RB_SEL(timer)| TIMER_RB_COUNT_ | BIT(6) | BIT(7);

	if(sys_outb(control_reg, read_back_command) != OK) return 1;
	if(sys_inb(TIMER_0+timer, &temp ) != OK) return 1;
	*st = (char) temp;

	return 0;

}

int timer_display_conf(unsigned char conf) {
	printf("\n**** TIMER CONFIGURATION ****\n\n");

	if(conf >> 7 & 0x01) printf("Timer output: 1 \n");
	else printf("Timer output: 0 \n");

	if(conf >> 6 & 0x01 ) printf("Timer null count: 1 \n");
	else printf("Timer null count: 0 \n");

	if((conf >> 5 & 0x01 ) && (conf >> 4 & 0x01 ))  printf("Type of access: LSB followed by MSB \n");
	else if (conf >> 5 && 0x01 ) printf("Type of access: MSB \n");
	else printf("Type of access: LSB \n");

	if((conf >> 1 & 0x01 ) && (conf >> 2 & 0x01 ))  printf("Operating mode %lu: Square wave \n",conf >> 1 & 0x03);
	else printf("Other operating mode: %lu\n",(conf >> 1 & 0x03)); //shifts one bit right and && with bitmask so we have only the 3 digits. Then print them

	if(conf & 0x01 ) printf("Counting mode: BCD \n\n");
	else printf("Counting mode: Binary \n\n");

	return 1;
}

int timer_test_square(unsigned long freq) {
	timer_set_square(0,freq);
	return 1;
}

int timer_test_int(unsigned long time) {
	int ipc_status,r, seconds = 0;
	message msg;
	int shift = timer_subscribe_int();

	while(seconds < time) { /* assuming the timer frequency is set to 60*/

		/* Get a request message. */
		if ( driver_receive(ANY, &msg, &ipc_status) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & BIT(shift)) { /* subscribed interrupt  bit 1 fica a 1, logo é 1*/
					timer_int_handler();
					if (counter%60 == 0){
						//as the frequency of interruptions is 60Hz as assumed, that means every 60 interrupts 1 second has passed
						//so whatever is inside this if-block happens each second
						seconds++; // increments the seconds counter
						printf("Hello\n!");
					};
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}
	timer_unsubscribe_int();
	return 0;
}

int timer_test_config(unsigned long timer) {
	char config;
	if(timer <= 2 && !timer_get_conf(timer,&config)) {
		return timer_display_conf(config);
	}
	else {
		printf("An error occured. Make sure your timer is 0, 1 or 2.\n");
		return 1;
	}
}
