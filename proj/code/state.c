#include "state.h"

void init() {

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
		if(isOutput()) drawOutputBox((char*) getBoxTitle(),(char*) getBoxText());
		else drawInputBox((char*) getBoxTitle(),(char*) getBoxText());

	}
	memcpy((char*)background,(char*) getBuffer(), getVideoMemSize());
}


void playIntro(){
	mainDraw();
	flipDisplay();
	sleep(1);
}


void kbc_consequences(int output) {

	switch(output) {

	case 2:
		enableBox(1,"DELETE","Do you want to delete the selected files?");
		setDeleteFlag();
		updateScreen();
		break;
	case 3:
		navigateLeft();
		updateScreen();
		break;
	case 4:
		navigateRight();
		updateScreen();
		break;
	case 5:
		navigateUp();
		updateScreen();
		break;
	case 6:
		navigateDown();
		updateScreen();
		break;
	case 7:
		openFolderByEnter();
		updateScreen();
		break;
	case 8:
		moveBack();
		updateScreen();
		break;
	case 9:
		setRenameFlag();
		enableBox(0,"RENAME",NULL);
		updateScreen();

	default:
		if(getRenameFlag() && output >= 10 && output <= 36) updateTextBox(output);
		updateScreen();

	}

}

void mouse_consequences(int output) {

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

		if(getRenameFlag() && isBoxConfirmed()) {
			check_rename_folder();
			updateScreen();
		}

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

				//INTERRUP��ES DO KEYBOARD

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

				//INTERRUP��ES DO RATO

				else if(msg.NOTIFY_ARG & BIT(shift_mouse)) {
					printf("MOUSE INTERRUPT\n");

					output = mouse_int_handler(&current_mouse_state);
					if(output == 2) mouse_consequences(output);

				}

				//INTERRUP��ES DO TIMER

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






void minixBootAnimation(unsigned int time) {

	vg_init(0x105);

	char**sprites[5] = {loading1, loading2, loading3, loading4, loading5};

	int shift_timer = timer_subscribe_int();

	int ipc_status,r, seconds = 0, running = 1;
	message msg;

	int index = 0;
	mainDraw();

	while(get_seconds()  < time) {

		if ( driver_receive(ANY, &msg, &ipc_status) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { // received notification
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: // hardware interrupt notification
				if (msg.NOTIFY_ARG & BIT(shift_timer)) {
					timer_int_handler();
					if(index > 4) break; else draw_sprite(centerImageX(135), 300, sprites[index]);
					if(index != 0) sleep(1);
				}
			default:
				break;
			}
		}
		flipDisplay();
		index++;
	}
	timer_unsubscribe_int();
}




