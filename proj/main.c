
#include <minix/drivers.h>

#include "state.h"

int main(int argc, char **argv) {
	/* Initialize service */
	init();
	playIntro();
	//minixBootAnimation(1);

	if(loop()) unsubscribe_devices();
	return 0;
}


//
//
//int minixBootAnimation(unsigned short time) {
//
//	vg_init(0x105);
//
//	//char *sprites[5] = {loading, loading2, loading3, loading4, loading5};
//
//	int shift_timer = timer_subscribe_int();
//
//	int ipc_status,r, seconds = 0, running = 1;
//	message msg;
//	unsigned long code;
//
//	mainDraw();
//	char dev[] = "Developers";
//	char names[] = "Filipe Gama Guilherme Routar";
//
//	draw_string(dev,480,290);
//	draw_string(names,420,300);
//
//	int index = 0;
//
//	printf("Timer flag: %d",timer_flag);
//
//	while(running && (get_seconds()  < time)) {
//		// Get a request message.
//		if ( driver_receive(ANY, &msg, &ipc_status) != 0 ) {
//			printf("driver_receive failed with: %d", r);
//			continue;
//		}
//		if (is_ipc_notify(ipc_status)) { // received notification
//			switch (_ENDPOINT_P(msg.m_source)) {
//			case HARDWARE: // hardware interrupt notification
//				if (msg.NOTIFY_ARG & BIT(shift_timer)) { // subscribed interrupt  bit 1 fica a 1, logo � 1
//					timer_int_handler();
//					//if(index > 4) break; else draw_sprite(480, 250, sprites[index]);
//					//if(index != 0) sleep(1);
//				}
//
//			default:
//				break; // no other notifications expected: do nothing
//			}
//		} else { // received a standard message, not a notification
//			// no standard messages expected: do nothing
//		}
//		flipDisplay();
//		index++;
//	}
//
//
//	timer_unsubscribe_int();
//
//	return 0;
//}
//
//




