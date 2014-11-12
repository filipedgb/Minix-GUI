#include "test4.h"
#include "mouse.h"

int test_packet(unsigned short cnt){
	char writecommand = 0xD4;

	int shift = mouse_subscribe_int();


//	printf("Write byte: %x\n",writecommand);
	kbc_input(writecommand);

	char enable_data_packets = 0xF4;

//	printf("Enable packets byte: %x\n",enable_data_packets);
	issue_command_mouse(enable_data_packets,-1);

	setMaxPackets(cnt);

	interruption_loop(shift);
}

int test_async(unsigned short idle_time) {
	char writecommand = 0 | BIT(2) | BIT(4) | BIT(6) | BIT(7);

//	printf("Write byte: %x\n",writecommand);
	kbc_input(writecommand);

	char enable_data_packets = 0 | BIT(2) | BIT(4) |  BIT(5) | BIT(6) | BIT(7);

//	printf("Enable packets byte: %x\n",enable_data_packets);
	issue_command_mouse(enable_data_packets,-1);

	setMaxPackets(99999);
	setTimerFlag();
	setTime((int)idle_time);
	interruption_loop();
}

int test_config(void) {
	unsigned long data;
	char writecommand = 0 | BIT(2) | BIT(4) | BIT(6) | BIT(7);
//	printf("Write byte: %x\n",writecommand);
	kbc_input(writecommand);

	char status_req =  0 | BIT(0) | BIT(3) |  BIT(5) | BIT(6) | BIT(7); // 0xE9 command

	issue_command_mouse(status_req,-1);

	read_config();

	print_mouse_config();

}

int test_gesture(short length, unsigned short tolerance) {
    /* To be completed ... */
}
