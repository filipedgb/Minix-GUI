#ifndef _SERIALPORT_
#define _SERIALPORT_



void set_dlab();
void reset_dlab();

void polled_sender(unsigned long ser_port, char toSend);

void polled_receiver(unsigned long ser_port, char* receivedChar);






#endif
