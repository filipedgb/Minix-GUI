#include "test3.h"
#include <minix/syslib.h>
#include <minix/drivers.h>
#include "i8042.h"

static int counter = 0;
static int hook_id = 0;

int keyboard_subscribe_int(void ) {
		int temp = hook_id; //integer between 0 and 31
        sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE ,&hook_id); // returns a hook id that you can then use to enable and disable irqs.
        sys_irqenable(&hook_id);
        return temp;
}

int keyboard_unsubscribe_int() {
        if (sys_irqrmpolicy(&hook_id)!= OK) return 1;
        return 0;
}


void keyboard_int_handler() {
	counter++;
}


int kbd_test_scan(unsigned short ass) {
	int ipc_status,r, seconds = 0;
		message msg;
		int shift = keyboard_subscribe_int();

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
		keyboard_unsubscribe_int();
		return 0;

}
int kbd_test_leds(unsigned short n, unsigned short *leds) {
    /* To be completed */
}
int kbd_test_timed_scan(unsigned short n) {
    /* To be completed */
}
