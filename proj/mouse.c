#include "mouse.h"
#include <stdlib.h>
#include <string.h>     /* strcat */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static unsigned char config[3];
static unsigned long packet[3];
static unsigned short total_packet_cnt = 0;
static unsigned short packet_counter = 0;
static int max_packets = 10;
static int state = 0;
static int total_dx = 0;
static int total_dy = 0;
static int length = 0;
static int tolerance = 0;
static int end_flag = 0;
static int gesture_enabled = 0;



void setTolerance(int val) {
	tolerance = val;
}
void setLength(int val) {
	length = val;
}

void setGesture() {
	gesture_enabled = 1;
}

void setMaxPackets(int max) {
	max_packets = max;
}

int mouse_subscribe_int(void ) {
	int temp = hook_id_3; //integer between 0 and 31
	sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE ,&hook_id_3); // returns a hook id that you can then use to enable and disable irqs.
	sys_irqenable(&hook_id_3);
	return temp;
}

int mouse_unsubscribe_int() {
	sys_irqdisable(&hook_id_3);
	if (sys_irqrmpolicy(&hook_id_3)!= OK) return 1;
	return 0;
}

//FUNCAO retirada da internet: http://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
const char *byte_to_binary(int x)
{
	static char b[9];
	b[0] = '\0';

	int z;
	for (z = 128; z > 0; z >>= 1)
	{
		strcat(b, ((x & z) == z) ? "1" : "0");
	}

	return b;
}

void updateState(mouse_state* this_state) {
	if(packet[0] >> 4 & 0x01) (*this_state).x += (packet[1]-255);
	else  (*this_state).x += packet[1];

	if ((*this_state).x < 0 ) (*this_state).x = 0;
	else if((*this_state).x > getHRES()-20 ) (*this_state).x = getHRES()-20;

	if(packet[0] >> 5 & 0x01)   (*this_state).y -= (packet[2]-255);
	else  (*this_state).y -= packet[2];

	if ((*this_state).y < 0 ) (*this_state).y = 0;
	else if((*this_state).y > getVRES()-18  ) (*this_state).y = getVRES()-18 ;


	 (*this_state).lb =  packet[0] & 0x01;
	 (*this_state).rb = packet[0] >> 2 & 0x01;
	 (*this_state).mb = packet[0] >> 1 & 0x01;
}

int mouse_int_handler(mouse_state* this_state) {

	unsigned long packetPart;
	//packetPart = kbc_output();
	if(sys_inb(OUT_BUF, &packetPart) != 0){
		printf("Error reading from OUT_BUF\n");
	}

	unsigned char p = (unsigned char)packetPart;

	total_packet_cnt++;


	if( !((p>> 3) & 1) && packet_counter == 0) {
	//if(packet_counter == 0 && (p & BIT(3)) == 0){
		printf("packet not sync: 0x%x\n",p);
		printf("Waiting to sync\n");
		return 1;
	}

	else if(packet_counter == 2) {
		packet[packet_counter] = p;
		packet_counter = 0;
		//print_packet();

		updateState(this_state);

		return 2;
	}
	else {
		packet[packet_counter] = p;
		packet_counter++;

		return 0;
	}


	/*


	packet[packet_counter++] = (unsigned char)packetPart;
	if(packet_counter == 2){
		packet_counter == 0;
		print_packet();
	}

	total_packet_cnt++;
	*/
}


void print_packet() {

	printf("B1=0x%x B2=0x%x B3=0x%x ",packet[0],packet[1],packet[2]);

	printf("LB=%d MB=%d RB=%d XOV=%d YOV=%d ",

			packet[0] & 0x01, packet[0] >> 2 & 0x01, packet[0] >> 1 & 0x01, packet[0] >> 6 & 0x01,packet[0] >> 7 & 0x01);

	if(packet[1] == 0) printf("X=0 ");

	else if(packet[0] >> 4 & 0x01) printf("X=%d ",packet[1]-255);
	else printf("X=%d ",packet[1]);

	if(packet[2] == 0) printf("Y=0\n");

	else if(packet[0] >> 5 & 0x01) printf("Y=%d\n",packet[2]-255);
	else printf("Y=%d\n",packet[2]);
	return;

}



/**
 *  Nota importante: Sempre que h� valores negativos no dx e dy n�o os consegui ler correctamente, aparecendo sempre -255 tanto movendo
 *  para a esquerda como para baixo. Portanto, para testar esta fun��o com a tolerancia vertical ter� de o fazer movendo o
 *  rato para cima, pois para baixo como os valores eram sempre -255 decidi ignorar. Para a esquerda ele detecta que houve movimento
 *  negativo simplesmente e faz reset, portanto tamb�m funciona nesse caso.
 *
 */

int gesture_state_machine(){

	int leftButton = packet[0] & 0x01;

	printf("total_dx = %d ",total_dx);
	printf("total_dy = %d \n",total_dy);


	switch(state) {
	case 0: //Initial
		printf("Entrou no estado inicial\n");
		if(leftButton) {
			printf("Left button foi premido\n");
			state++; // se houve movimento positivo em x come�ou a desenhar o gesture
		}
		break;
	case 1: //Drawing
		printf("Est� a desenhar\n");

		total_dx += packet[1];
		if( (packet[0] >> 5 & 0x01) == 0) total_dy += packet[2];


		if(packet[0] >> 4 & 0x01) { //se o rato voltar para tras, come�a tudo de novo
			printf("Rato voltou atr�s\n");
			total_dx = 0;
			total_dy = 0;
			state = 0;
		}

		if(leftButton == 0 || (total_dy > tolerance)) {  //se levantou o bot�o esquerdo ou subiu demasiado, volta ao in�cio
			if(!leftButton)printf("Levantou o bot�o\n");
			else printf("Excedeu a tolerancia\n");

			state = 0;
			total_dx = 0; total_dy = 0;
		}

		else if (total_dx >= length) { // se o movimento total em dx j� � igual ao length desejado para gesture termina
			state++;
		}

		break;
	case 2: //Completed
		printf("Gesture completed!\n");
		end_flag = 1;
		return 1;
		break;
	}

	return 0;

}



void read_config() {
	unsigned long data;
	kbc_output(&data); // byte 1
	config[0] = (char) data;

	kbc_output(&data); // byte 2
	config[1] = (char) data;

	kbc_output(&data); // byte 3
	config[2] = (char) data;

}



void print_mouse_config() {

	printf("\n**** MOUSE CONFIGURATION ****\n\n");

	// BYTE 1
	printf("Remote: "); //remote
	if(config[0] >> 6 & 0x01) printf("Remote polled mode\n");
	else printf("Stream mode\n");

	printf("Enable: "); //enable
	if(config[0] >> 5 & 0x01 ) printf("Data reporting enabled\n");
	else printf("Data reporting disabled\n");

	printf("Scaling: "); //scaling
	if(config[0] >> 4 & 0x01)  printf(" Scaling is 2:1\n");
	else printf("Scaling is 1:1\n");

	printf("\nButtons: \n");

	if(config[0] >> 2 & 0x01 ) printf("Left button is currently pressed\n");
	else printf("Left button is not pressed\n");

	if(config[0] >> 1 & 0x01 ) printf("Middle button is currently pressed\n");
	else printf("Middle button is not pressed\n");

	if(config[0] & 0x01) printf("Right button is currently pressed\n");
	else printf("Right button is not pressed\n");

	//BYTE 2
	printf("\nResolution: %d\n",config[1]);

	//BYTE 3
	printf("\nSample Rate: %d\n",config[2]);

}

int kbc_write(unsigned long port, unsigned char byte){
	printf("0x%02X -> 0x%02X\n", byte, port);

	if(sys_outb(port, byte) != 0){
		printf("error in kbc_write\n");
		return -1;
	}

	return 0;
}

int kbc_read(unsigned long port, unsigned char *byte){
	unsigned long buf;
	if(sys_inb(port, &buf) != OK){
		printf("erro em kbc_read\n");
		return -1;
	}

	*byte = (unsigned char)buf;

	printf("0x%02X <- 0x%02X\n", byte, port);
}

/*FUNCTION FROM SLIDE 21: http://web.fe.up.pt/~pfs/aulas/lcom2014/at/5kbrd.pdf*/
int kbc_input(char kbc_command)  { // issues command to kbc

	//unsigned long stat;
	unsigned char stat;

	//sys_inb(STAT_REG, &stat); /* assuming it returns OK */
	kbc_read(STAT_REG, &stat);
	/* loop while 8042 input buffer is not empty */
	if( (stat & IBF) == 0 ) {
		//if( sys_outb(KBC_CMD_REG, kbc_command) != OK) {
		if( kbc_write(KBC_CMD_REG, kbc_command) != 0) {
			printf("Error sending kbc command\n");
			return 1; /* no args command */
		}

		printf("KBC command written sucessfully\n");
		return 0;
	}
	tickdelay(micros_to_ticks(DELAY_US));

}

//FUNCTION FROM SLIDE 22: http://web.fe.up.pt/~pfs/aulas/lcom2014/at/5kbrd.pdf
int kbc_output() {
	unsigned long stat, data;

	while(1) {
		printf("Preso no loop\n");

		sys_inb(STAT_REG, &stat);
		if(stat & OBF) {
			sys_inb(OUT_BUF, &data);
			if ( (stat &(PAR_ERR | TO_ERR)) == 0 )
				return data;
			else
				return -1;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
	return -1;
}


int issue_command_mouse(unsigned char command, unsigned char argument) {
	// If you want to issue a command without argument, pass -1 as second parameter

	//unsigned long ack_byte;
	unsigned char ack_byte;

	//sys_outb(IO_BUF_PORT, command);
	kbc_write(IO_BUF_PORT, command);
	//sys_inb(IO_BUF_PORT, &ack_byte);
	kbc_read(IO_BUF_PORT, &ack_byte);

	if (ack_byte == 0xFA) {
		printf("Mouse command aknowledged!\n");
	}
	else {
		printf("Failed, command no ack\n");
	}

	/*
	if(argument != -1) {
		//if (sys_outb(IO_BUF_PORT, argument) != OK ) return 1;
		if (kbc_write(IO_BUF_PORT, argument) != OK ) return 1;

		sys_inb(IO_BUF_PORT, &ack_byte);
		if (ack_byte != 0xFA) return 1;

	}

	else ("No arguments\n");
	*/

	return 0;

}



