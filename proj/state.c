#include "state.h"

void init() {
	sef_startup();
	subscribe_devices();
	getSubFolders(".");
	initButtons();

	background = (char*) malloc (getVideoMemSize());
	memcpy((char*)background,(char*) getBuffer(), getVideoMemSize());

}

void subscribe_devices() {
	vg_init(0x105);

	shift_mouse = mouse_subscribe_int();
	shift_keyboard = keyboard_subscribe_int();
	shift_timer = timer_subscribe_int();

	kbc_input(KBC_WRITE_COMMAND);
	issue_command_mouse(0xF6,-1);
	kbc_input(KBC_WRITE_COMMAND);
	issue_command_mouse(ENABLE_STREAM_MODE,-1);
	kbc_input(KBC_WRITE_COMMAND);
	issue_command_mouse(ENABLE_DATA_PACKETS,-1);
}

void unsubscribe_devices() {
	keyboard_unsubscribe_int();
	timer_unsubscribe_int();
	mouse_unsubscribe_int();
	vg_exit();
}


void updateScreen() {
	cleanScreen();
	drawMainMenu();
	drawFolders();

	if(isBox()) {
		if(isOutput()) drawOutputBox(getBoxText());
		else drawInputBox();

	}
	memcpy((char*)background,(char*) getBuffer(), getVideoMemSize());
}


void playIntro(){
	mainDraw();
	flipDisplay();
	sleep(1);
}


void kbc_consequences(int output) {

	if(output == 2) {
		enableBox(1,"Do you want to delete the selected files?");
		setDeleteFlag();
		updateScreen();

	}
	else if (output == 3) {
		navigateLeft();
		updateScreen();
	}

	else if (output == 4) {
		navigateRight();
		updateScreen();
	}
	else if (output == 5) {
		navigateUp();
		updateScreen();
	}
	else if (output == 6) {
		navigateDown();
		updateScreen();
	}
	else if (output == 7) {
		openFolderByEnter();
		updateScreen();
	}
	else if (output == 8) {
		moveBack();
		updateScreen();
	}




}

void mouse_consequences(int output) {
	if(output == 2) { // So faz verificações no final de cada pacote (return 2 do handler)

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
			memcpy((char*)background, (char*) getBuffer(), getVideoMemSize());

		}

	}
}




int loop() {
	int output;
	int menu_open = 0;

	int ipc_status,r, seconds = 0, running = 1;
	message msg;
	unsigned long code;

	int ticker = 0;
	int estado = 0;
	int esc_pressed = 0;

	updateScreen();

	while(running) {

		if(getDeleteFlag() && isBoxConfirmed()) {
			check_delete_files();
			updateScreen();
		}

		if(isBoxConfirmed() && getTurnOffFlag()) {
			printf("entrou aqui");
			vg_exit();
			running = 0;

		}


		/* Get a request message. */
		if ( driver_receive(ANY, &msg, &ipc_status) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */

				//INTERRUPÇÕES DO KEYBOARD

				if (msg.NOTIFY_ARG & BIT(shift_keyboard)) {
					output = keyboard_int_handler_C(&code);

					if(output == 1) {
						if(esc_pressed) {
							if(get_counter() < 25) {
								running = 0;
							}
						}

						reset_counter();
						esc_pressed = 1;
					}

					kbc_consequences(output);

				}

				//INTERRUPÇÕES DO RATO

				else if(msg.NOTIFY_ARG & BIT(shift_mouse)) {
					printf("MOUSE INTERRUPT\n");

					output = mouse_int_handler(&current_mouse_state);
					mouse_consequences(output);

				}

				//INTERRUPÇÕES DO TIMER

				else if (msg.NOTIFY_ARG & BIT(shift_timer)) {
					//printf("TIMER INTERRUPT\n");

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

	return 1;


}
