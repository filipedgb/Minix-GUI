#include "mouse.h"
#include <stdlib.h>
#include <string.h>     /* strcat */


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

static int mouse_x=0;
static int mouse_y=0;
static int mouse_lc=0;
static int mouse_rc=0;
static int mouse_updated=0;

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


void setTimerFlag() {
	timer_flag = 1;
}

void setTime(int seconds) {
	tempo = seconds;
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

//FUNÇÃO retirada da internet: http://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
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

int mouse_int_handler() {

	unsigned long packetPart;
	//packetPart = kbc_output();
	sys_inb(OUT_BUF, &packetPart);


	if( !((packetPart >> 3) & 1) && packet_counter == 0) {
		printf("packet not sync: 0x%x\n",packetPart);
		printf("Waiting to sync\n");
		return 1;
	}

	else if(packet_counter == 2) {
		packet[packet_counter] = packetPart;
		packet_counter = 0;
		print_packet();
	}

	else {
		packet[packet_counter] = packetPart;
		packet_counter++;

	}

	total_packet_cnt++;
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
 *  Nota importante: Sempre que há valores negativos no dx e dy não os consegui ler correctamente, aparecendo sempre -255 tanto movendo
 *  para a esquerda como para baixo. Portanto, para testar esta função com a tolerancia vertical terá de o fazer movendo o
 *  rato para cima, pois para baixo como os valores eram sempre -255 decidi ignorar. Para a esquerda ele detecta que houve movimento
 *  negativo simplesmente e faz reset, portanto também funciona nesse caso.
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
			state++; // se houve movimento positivo em x começou a desenhar o gesture
		}
		break;
	case 1: //Drawing
		printf("Está a desenhar\n");

		total_dx += packet[1];
		if( (packet[0] >> 5 & 0x01) == 0) total_dy += packet[2];


		if(packet[0] >> 4 & 0x01) { //se o rato voltar para tras, começa tudo de novo
			printf("Rato voltou atrás\n");
			total_dx = 0;
			total_dy = 0;
			state = 0;
		}

		if(leftButton == 0 || (total_dy > tolerance)) {  //se levantou o botão esquerdo ou subiu demasiado, volta ao início
			if(!leftButton)printf("Levantou o botão\n");
			else printf("Excedeu a tolerancia\n");

			state = 0;
			total_dx = 0; total_dy = 0;
		}

		else if (total_dx >= length) { // se o movimento total em dx já é igual ao length desejado para gesture termina
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



void interruption_loop(int shift) {
	int ipc_status,r, seconds = 0;
	message msg;
	int shift_timer = timer_subscribe_int();

	while( (total_packet_cnt < max_packets) && (get_seconds() < tempo) && (end_flag == 0)) { /* assuming the timer frequency is set to 60*/

		/* Get a request message. */
		if ( driver_receive(ANY, &msg, &ipc_status) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & BIT(shift)) { /* subscribed interrupt  bit 1 fica a 1, logo Ã© 1*/
					mouse_int_handler();
					reset_cronometer();
				}

				else if(msg.NOTIFY_ARG & BIT(shift_timer) && timer_flag) {
					timer_int_handler();
				}


				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	printf("Terminating...\n");

	mouse_unsubscribe_int();
	timer_unsubscribe_int();
	return;
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


/*FUNCTION FROM SLIDE 21: http://web.fe.up.pt/~pfs/aulas/lcom2014/at/5kbrd.pdf*/
int kbc_input(char kbc_command)  { // issues command to kbc

	unsigned long stat;

	sys_inb(STAT_REG, &stat); /* assuming it returns OK */
	/* loop while 8042 input buffer is not empty */
	if( (stat & IBF) == 0 ) {
		if( sys_outb(KBC_CMD_REG, kbc_command) != OK) {
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

	unsigned long ack_byte;

	sys_outb(IO_BUF_PORT, command);
	sys_inb(IO_BUF_PORT, &ack_byte);

	if (ack_byte == 0xFA) {
		printf("Mouse command aknowledged!\n");
	}
	else {
		printf("Failed, command no ack\n");
	}

	if(argument != -1) {
		if (sys_outb(IO_BUF_PORT, argument) != OK ) return 1;

		sys_inb(IO_BUF_PORT, &ack_byte);
		if (ack_byte != 0xFA) return 1;

	}

	else ("No arguments\n");

	return 0;

}



