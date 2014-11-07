#include "test4.h"
#include "mouse.h"

int test_packet(unsigned short cnt){

	char writecommand = 0 | BIT(2) | BIT(4) | BIT(6) | BIT(7);

//	printf("Write byte: %x\n",writecommand);
	kbc_input(writecommand);

	char enable_data_packets = 0 | BIT(2) | BIT(4) |  BIT(5) | BIT(6) | BIT(7);

//	printf("Enable packets byte: %x\n",enable_data_packets);
	issue_command_mouse(enable_data_packets,-1);

	interruption_loop();



}

int test_async(unsigned short idle_time) {
    /* To be completed ... */
}

int test_config(void) {
    /* To be completed ... */
}

int test_gesture(short length, unsigned short tolerance) {
    /* To be completed ... */
}
