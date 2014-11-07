#include "mouse.h"

static unsigned char packet[3];
static unsigned short total_packet_cnt = 0;
static unsigned short packet_counter = 0;


int mouse_subscribe_int(void ) {
	int temp = hook_id_3; //integer between 0 and 31
	sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE ,&hook_id_3); // returns a hook id that you can then use to enable and disable irqs.
	sys_irqenable(&hook_id_3);
	return temp;
}

int mouse_unsubscribe_int() {
	if (sys_irqrmpolicy(&hook_id_3)!= OK) return 1;
	return 0;
}


int mouse_int_handler() {
	unsigned long info;

	sys_inb(OUT_BUF,&info);


	if(packet_counter == 0 && (info >> 3 & 0x01) ) return 1; // "bit 3 of byte 1 must be 1"-verification

	packet[packet_counter] = info;

	if(packet_counter == 2) {
		packet_counter = 0;
		print_packet();
	}

	packet_counter++;
	total_packet_cnt++;
	if(total_packet_cnt == 18) return 1;

	return 0;


}



void print_packet() {
	printf("B1=0x%x B2=0x%x B3=0x%x ",packet[0],packet[1],packet[2]);
	printf("LB=%d MB=%d RB=%d XOV=%d YOV=%d X=%d Y=%d\n",
			packet[0] & 0x01, packet[0] >> 2 & 0x01, packet[0] >> 1 & 0x01, packet[0] >> 6 & 0x01,packet[0] >> 7 & 0x01,
			packet[1],packet[2]);

	return;

}


void interruption_loop() {
	int ipc_status,r, seconds = 0;
	message msg;
	int shift = mouse_subscribe_int();

	int i = 0;

	while(total_packet_cnt < 500) { /* assuming the timer frequency is set to 60*/

		/* Get a request message. */
		if ( driver_receive(ANY, &msg, &ipc_status) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & BIT(shift)) { /* subscribed interrupt  bit 1 fica a 1, logo é 1*/
					mouse_int_handler();
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	mouse_unsubscribe_int();
	return;
}
/*FUNCTION FROM SLIDE 21: http://web.fe.up.pt/~pfs/aulas/lcom2014/at/5kbrd.pdf*/
int kbc_input(char kbc_command)  { // issues command to kbc

	unsigned long stat;

	sys_inb(STAT_REG, &stat); /* assuming it returns OK */
	/* loop while 8042 input buffer is not empty */
	if( (stat & IBF) == 0 ) {
		if( sys_outb(KBC_CMD_REG, kbc_command) != OK) {
			return 1; /* no args command */
		}
		return 0;
	}
	tickdelay(micros_to_ticks(DELAY_US));

}

/*FUNCTION FROM SLIDE 22: http://web.fe.up.pt/~pfs/aulas/lcom2014/at/5kbrd.pdf
int kbc_output(unsigned long* data) {
	unsigned long stat;

	while( 1 ) {
		sys_inb(STAT_REG, &stat); // assuming it returns OK
		// loop while 8042 output buffer is empty
		if( stat & OBF ) {
			sys_inb(OUT_BUF, data); // assuming it returns OK
			if ( (stat &(PAR_ERR | TO_ERR)) == 0 )
				return *data;
			else
				return -1;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}

} */

int issue_command_mouse(unsigned char command, unsigned char argument) {
	// If you want to issue a command without argument, pass -1 as second parameter

	unsigned long ack_byte;

	sys_outb(IO_BUF_PORT, command);
	sys_inb(IO_BUF_PORT, &ack_byte);

	if (ack_byte != 0xFA) {
		printf("Command not aknowledged!\n");
		return 1;
	}

	if(argument != -1) {
		if (sys_outb(IO_BUF_PORT, argument) != OK ) return 1;

		sys_inb(IO_BUF_PORT, &ack_byte);
		if (ack_byte != 0xFA) return 1;

	}

	else ("No arguments\n");

	return 0;

}


void setTimerFlag() {
	timer_flag = 1;
}


void setTime(int seconds) {
	time = seconds;
}

