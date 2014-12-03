#include "keyboard.h"
#include "read_xpm.h"
#include "timer.h"

#include "sprite.h"

#include <minix/drivers.h>

static int proc_args(int argc, char *argv[]);
static unsigned long parse_ulong(char *str, int base);
static long parse_long(char *str, int base);
static void print_usage(char *argv[]);

int main(int argc, char **argv) {
	/* Initialize service */
	sef_startup();

	vg_init(0x105);

	int shiftkeyboard = keyboard_subscribe_int();
	int shift_timer = timer_subscribe_int();

	int ipc_status,r, seconds = 0, running = 1;
	message msg;
	unsigned long code;

	int esc_pressed = 0;


	while(running) {
		/* Get a request message. */
		if ( driver_receive(ANY, &msg, &ipc_status) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & BIT(shiftkeyboard)) { /* subscribed interrupt  bit 1 fica a 1, logo é 1*/
					if(keyboard_int_handler_C(&code)) {

						if(esc_pressed) {
							if(get_counter() < 25) {
								running = 0;
							}
						}

						reset_counter();
						esc_pressed = 1;


					}


				}

				else if (msg.NOTIFY_ARG & BIT(shift_timer)) { /* subscribed interrupt  bit 1 fica a 1, logo � 1*/
					//	printf("\n Entrou aqui. Counter %d \n", get_counter());
					timer_int_handler();

				}

			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	keyboard_unsubscribe_int();
	timer_unsubscribe_int();

	vg_exit();

	return 0;
}



