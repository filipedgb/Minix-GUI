#include "test5.h"
#include "keyboard.h"
#include "read_xpm.h"
#include "timer.h"

#include "sprite.h"

void *test_init(unsigned short mode, unsigned short delay) {
	vg_init(mode);
	sleep(delay);
	vg_exit();

}


int test_square(unsigned short x, unsigned short y, unsigned short size, unsigned long color) {
	int shift = keyboard_subscribe_int();

	vg_init(0x105);
	draw_rectangle(x,y,size,size,color);

	if(receiver_loop(shift,-1)) {
		vg_exit();
		keyboard_unsubscribe_int();
	}

	return 0;
}

int test_line(unsigned short xi, unsigned short yi,
		unsigned short xf, unsigned short yf, unsigned long color) {

	int shift = keyboard_subscribe_int();

	vg_init(0x105);

	draw_line(xi,yi,xf,yf,color);

	if(receiver_loop(shift,-1)) {
		vg_exit();
		keyboard_unsubscribe_int();
	}

	return 0;
}

int test_xpm(unsigned short xi, unsigned short yi, char *xpm[]) {

	vg_init(0x105);

	draw_sprite(xi, yi, xpm);

	sleep(2);

	vg_exit();

	return 0;

	//POR AQUI PARA SAIR COM ESC;

}

int test_move(unsigned short xi, unsigned short yi, char *xpm[],
		unsigned short hor, short delta, unsigned short time) {

	vg_init(0x105);

	int shiftkeyboard = keyboard_subscribe_int();
	int shift_timer = timer_subscribe_int();

	int ipc_status,r, seconds = 0, running = 1;
	message msg;
	unsigned long code;


	printf("Timer flag: %d",timer_flag);

	while(running && (get_seconds()  < time)) {
		/* Get a request message. */
		if ( driver_receive(ANY, &msg, &ipc_status) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & BIT(shiftkeyboard)) { /* subscribed interrupt  bit 1 fica a 1, logo é 1*/
					if(keyboard_int_handler_C(&code)) running = 0;
				//	printf("ESTA AQUI");

				//	printf("Seconds: %d\n",get_seconds());

				}

				else if (msg.NOTIFY_ARG & BIT(shift_timer)) { /* subscribed interrupt  bit 1 fica a 1, logo � 1*/
				//	printf("\n Entrou aqui. Counter %d \n", get_counter());
					timer_int_handler();

					int inc = (get_counter()*delta)/(60*time);

				//	printf("xi: %d, yi: %d, inc: %d\n",xi,yi,inc);

					if (hor == 0) {
						draw_sprite(xi, yi + inc, xpm); //vertical

					}
					else {
						draw_sprite(xi + inc, yi, xpm); //horizontal
					}
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
	vg_exit();

	return 0;
}

int test_controller() {
	return 0;
}


