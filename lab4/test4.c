#include "test4.h"
#include "mouse.h"

int test_packet(unsigned short cnt){
	int shift = mouse_subscribe_int();

	kbc_input(KBC_WRITE_COMMAND);
	issue_command_mouse(ENABLE_DATA_PACKETS,-1);

	setMaxPackets(cnt);

	interruption_loop(shift);

	return 0;
}

int test_async(unsigned short idle_time) {
	int shift = mouse_subscribe_int();

	kbc_input(KBC_WRITE_COMMAND);
	issue_command_mouse(ENABLE_DATA_PACKETS,-1);

	setMaxPackets(99999);
	setTimerFlag();
	setTime((int)idle_time);

	interruption_loop(shift);

	return 0;
}

int test_config(void) {
	mouse_subscribe_int();

	kbc_input(KBC_WRITE_COMMAND);
	issue_command_mouse(STATUS_REQUEST,-1);

	read_config();
	print_mouse_config();
	mouse_unsubscribe_int();

	return 0;

}

int test_gesture(short length, unsigned short tolerance) {
	int shift = mouse_subscribe_int();

	kbc_input(KBC_WRITE_COMMAND);
	issue_command_mouse(ENABLE_DATA_PACKETS,-1);

	setMaxPackets(99999);
	setTolerance(tolerance);
	setLength(length);
	setGesture();

	interruption_loop(shift);

}
