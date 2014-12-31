#include "serialport.h"

#define SER_OVERRUN_ERR (1<<1)
#define SER_PARITY_ERR (1<<2)
#define SER_FRAME_ERR (1<<3)


void polled_sender(unsigned long ser_port, char toSend) {

	unsigned long lsr,st;
	/* no error checking */

	if( sys_inb(ser_port + SP_LINE_STATUS, &st) != OK ) {
		printf("Error in sys_inb -> polled_Sender");
		return;
	}
	else if  ( st & (SER_OVERRUN_ERR | SER_PARITY_ERR | SER_FRAME_ERR) ) {
		printf("Error in sender\n");
		return;
	}


	/* busy wait for transmitter ready */
	while( !(lsr & SER_TX_RDY) ) {
		tickdelay(micros_to_ticks(20000));
		sys_inb(ser_port + SP_LINE_STATUS, &lsr);
	}

	/* send character */
	sys_outb(ser_port+SP_TRANSMITTER, toSend);

}


void polled_receiver(unsigned long ser_port, char* receivedChar) {

	unsigned long receive;
	unsigned long lsr;

	while( !(lsr & SER_RCV_RDY) ) {
		tickdelay(micros_to_ticks(500));
		sys_inb(ser_port + SP_LINE_STATUS, &lsr);
	}

	sys_inb(ser_port+SP_RECEIVER_BUF,&receive);
	(*receivedChar) = receive;
}
