#include "keyboard.h"
#include "read_xpm.h"
#include "timer.h"
#include "mouse.h"
#include "interface.h"
#include "rtc.h"
#include "video_gr.h"

#include "sprite.h"

#include <minix/drivers.h>

static int proc_args(int argc, char *argv[]);
static unsigned long parse_ulong(char *str, int base);
static long parse_long(char *str, int base);
static void print_usage(char *argv[]);

static char *background;



int main(int argc, char **argv) {
	/* Initialize service */
	sef_startup();

	vg_init(0x105);

	int shift_mouse = mouse_subscribe_int();

	int shiftkeyboard = keyboard_subscribe_int();


	int shift_timer = timer_subscribe_int();

	mouse_state current_mouse_state;
	rtc_state current_rtc_state;


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
	int ticker = 0;
	int updated = 0;
	int estado = 0;


	background = (char*) malloc (getVideoMemSize());

	getSubFolders(".");

	cleanScreen();
	drawFolders();
	drawMainMenu();


	memcpy(background, getBuffer(), getVideoMemSize());



	while(running) {




		/* Get a request message. */
		if ( driver_receive(ANY, &msg, &ipc_status) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & BIT(shiftkeyboard)) { /* subscribed interrupt  bit 1 fica a 1, logo Ã© 1*/
					//	printf("KEYBOARD INTERRUPT\n");


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
					//cleanCursor(current_mouse_state);

					if(mouse_int_handler(&current_mouse_state) == 2 && current_mouse_state.lb == 1) {

						switch(estado) {

						case 0:
							if(check_mouse_click(current_mouse_state) == 2) {

								cleanScreen();
								drawFolders();
								drawMainMenu();
								memcpy(background, getBuffer(), getVideoMemSize());

							}

							estado++;
							reset_counter();
							break;

						case 1:
							if(get_counter() < 25){

								if(check_mouse_double_click(current_mouse_state)) {
									cleanScreen();
									drawFolders();
									drawMainMenu();
									memcpy(background, getBuffer(), getVideoMemSize());
								}


								printf("Entrou aqui\n");
							}
							else {
								estado = 0;
							}

							break;


						}
						//printf("Cursor posição x: %d  y: %d\n",current_mouse_state.x,current_mouse_state.y);
					}

					updated = 1;

				}
				else if (msg.NOTIFY_ARG & BIT(shift_timer)) {
					//printf("TIMER INTERRUPT\n");
					ticker++;

					setDisplay(background);
					get_clock(&current_rtc_state);
					drawClock(current_rtc_state);
					drawCursor(current_mouse_state);

					timer_int_handler();

					if(ticker%2 == 0) {
						//printf("H1: %d, M1: %d, S1: %d \n",current_rtc_state.hours, current_rtc_state.minutes, current_rtc_state.seconds);


						if(updated) {

							updated = 0;
						}




					}


				}

			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}

		flipDisplay();

	}

	keyboard_unsubscribe_int();
	timer_unsubscribe_int();
	mouse_unsubscribe_int();
	vg_exit();

	return 0;
}



