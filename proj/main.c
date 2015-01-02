
#include <minix/drivers.h>

#include "state.h"

int main(int argc, char **argv) {

	/* Initialize service */
	sef_startup();

	minixBootAnimation(1);
	init();

	if(loop()) unsubscribe_devices();
	return 0;
}




void minixBootAnimation(unsigned int time) {

	vg_init(0x105);

	char *sprites[5] = {loading1, loading2, loading3, loading4, loading5};

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






