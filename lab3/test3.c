#include "test3.h"
#include <minix/syslib.h>
#include <minix/drivers.h>
#include "headers.h"

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

void loop() {
	int ipc_status,r, seconds = 0, running = 1;
	message msg;
	int shift = keyboard_subscribe_int();
	unsigned long code;


	while(running) { /* 10 seconds hardcoded just for testing */
		/* Get a request message. */
		if ( driver_receive(ANY, &msg, &ipc_status) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & BIT(shift)) { /* subscribed interrupt  bit 1 fica a 1, logo é 1*/
					keyboard_int_handler();

					sys_inb(OUT_BUF,&code);

					if(code ==

					if(code & 0x80 == 1)  {
						printf("Break code: %2x\n",code);
					}
					else printf("Make code: %2x\n", code);

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


}

int kbd_test_scan(unsigned short ass) {

	loop();

	return 0;

}
int kbd_test_leds(unsigned short n, unsigned short *leds) {
	/* To be completed */
}
int kbd_test_timed_scan(unsigned short n) {
	/* To be completed */
}
