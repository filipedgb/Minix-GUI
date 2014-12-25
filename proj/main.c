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

	int menu_open = 0;

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

					int output = keyboard_int_handler_C(&code);

					if(output == 1) {
						if(esc_pressed) {
							if(get_counter() < 25) {
								running = 0;
							}
						}

						reset_counter();
						esc_pressed = 1;
					}

					else if(output == 2) {
						check_delete_files();
						cleanScreen();
						drawFolders();
						drawMainMenu();
						if(menu_open) drawRightClickMenu(current_mouse_state);

						memcpy(background, getBuffer(), getVideoMemSize());
					}
				}

				else if(msg.NOTIFY_ARG & BIT(shift_mouse)) {
					printf("MOUSE INTERRUPT\n");
					//cleanCursor(current_mouse_state);

					int output = mouse_int_handler(&current_mouse_state);

					if(output == 2) { // Só há verificações lógicas no final de cada pacote (return 2 do handler)

						if(current_mouse_state.lb == 1) {
							if(get_counter() > 25) {
								check_mouse_click(current_mouse_state);
							}
							else {
								check_mouse_double_click(current_mouse_state);
							}

							reset_counter();
							updateScreen();


						}

						else if(current_mouse_state.rb == 1 && check_mouse_click(current_mouse_state) == 3) {
							updateScreen();
							drawRightClickMenu(current_mouse_state);
							memcpy(background, getBuffer(), getVideoMemSize());

						}

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


void updateScreen() {
	cleanScreen();
	drawMainMenu();
	drawFolders();
	memcpy(background, getBuffer(), getVideoMemSize());
}



