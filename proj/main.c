#include "keyboard.h"
#include "read_xpm.h"
#include "timer.h"
#include "mouse.h"
#include "interface.h"

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



	int shift_mouse = mouse_subscribe_int();

	int shiftkeyboard = keyboard_subscribe_int();


	int shift_timer = timer_subscribe_int();

	mouse_state current_mouse_state;

	kbc_input(KBC_WRITE_COMMAND);
	issue_command_mouse(0xF6,-1);
	kbc_input(KBC_WRITE_COMMAND);
	issue_command_mouse(ENABLE_STREAM_MODE,-1);
	kbc_input(KBC_WRITE_COMMAND);
	issue_command_mouse(ENABLE_DATA_PACKETS,-1);


	int ipc_status,r, seconds = 0, running = 1;
	message msg;
	unsigned long code;

	int esc_pressed = 0;


	while(running && get_seconds() < 60) {
		/* Get a request message. */
		if ( driver_receive(ANY, &msg, &ipc_status) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & BIT(shiftkeyboard)) { /* subscribed interrupt  bit 1 fica a 1, logo Ã© 1*/
					printf("KEYBOARD INTERRUPT\n");


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

				else if(msg.NOTIFY_ARG & BIT(shift_mouse)) {
					printf("MOUSE INTERRUPT\n");
					mouse_int_handler(&current_mouse_state);
					drawCursor(current_mouse_state);

					printf("Cursor posição x: %d  y: %d\n",current_mouse_state.x,current_mouse_state.y);


				}
				else if (msg.NOTIFY_ARG & BIT(shift_timer)) {
					//printf("TIMER INTERRUPT\n");
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
	mouse_unsubscribe_int();
	vg_exit();

	return 0;
}



