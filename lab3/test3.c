#include "test3.h"
#include <minix/syslib.h>
#include <minix/drivers.h>
#include "headers.h"
#include "i8254.h"
//#include "timer.h"

static int counter2 = 0;
static int counter = 0;
static int hook_id_2 = 1;
static int hook_id = 0;
static int timer_flag = 0;
static int assembly_flag = 0;
static int time = 5;

int keyboard_subscribe_int(void ) {
	int temp = hook_id_2; //integer between 0 and 31
	sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE ,&hook_id_2); // returns a hook id that you can then use to enable and disable irqs.
	sys_irqenable(&hook_id_2);
	return temp;
}

int keyboard_unsubscribe_int() {
	if (sys_irqrmpolicy(&hook_id_2)!= OK) return 1;
	return 0;
}


int keyboard_int_handler() {
	unsigned long code;

	kbc_output(&code); // corre a fun��o que l� o output do KBC
	//sys_inb(OUT_BUF,&code); // vai buscar o c�digo da tecla ao output buffer

	if (code == ESC_BREAK_CODE) {
		printf("Escape break code: %2x.\nTerminating...\n",code);
		return 1;
	}

	else if(code >> 7 & 0x01 == 1)  { // se o bit mais significativo se encontra a 1, ent�o trata-se de um break code
		printf("Break code: %2x\n",code);
	}

	else printf("Make code: %2x\n", code); // otherwise � um make code

	return 0;
}

void timer_int_handler() {
	counter++;
}

int timer_subscribe_int(void ) {
	int temp = hook_id; //integer between 0 and 31
	sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE,&hook_id); // returns a hook id that you can then use to enable and disable irqs.
	sys_irqenable(&hook_id);
	return temp;
}

int timer_unsubscribe_int() {
	if (sys_irqrmpolicy(&hook_id)!= OK) return 1;
	return 0;
}

void receiver_loop() {
	int ipc_status,r, seconds = 0, running = 1;
	message msg;

	int shift = keyboard_subscribe_int();
	int shift_timer;
	if(timer_flag) shift_timer = timer_subscribe_int();



	while(running && (seconds < time)) {
		/* Get a request message. */
		if ( driver_receive(ANY, &msg, &ipc_status) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & BIT(shift)) { /* subscribed interrupt  bit 1 fica a 1, logo é 1*/

					if(keyboard_int_handler()) running = 0;
					else seconds = 0;

				}

				else if (msg.NOTIFY_ARG & BIT(shift_timer) && timer_flag) { /* subscribed interrupt  bit 1 fica a 1, logo é 1*/
					//printf("\n Entrou aqui. Counter %d \n", counter);
					timer_int_handler();
					if (counter%60 == 0){
						//as the frequency of interruptions is 60Hz as assumed, that means every 60 interrupts 1 second has passed
						//so whatever is inside this if-block happens each second
						seconds++; // increments the seconds counter
						//printf("\n Segundos: %d \n", seconds);
					};
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	if(seconds >= time) {
		printf("\nTimeout. Terminating...\n");
	}


	keyboard_unsubscribe_int();
	timer_unsubscribe_int();
	return;


}



/*FUNCTION FROM SLIDE 21: http://web.fe.up.pt/~pfs/aulas/lcom2014/at/5kbrd.pdf*/
int kbc_input(char kbc_command)  {

	unsigned long stat;

	while( 1 ) {
		sys_inb(STAT_REG, &stat); /* assuming it returns OK */
		/* loop while 8042 input buffer is not empty */
		if( (stat & IBF) == 0 ) {
			if( sys_outb(KBC_CMD_REG, kbc_command) != OK) {
				printf("Erro no sys_outb");
				return 1; /* no args command */
			}
			printf("gets here 1");
			return 0;
		}
		printf("gets here 2");
		tickdelay(micros_to_ticks(DELAY_US));
	}
}

/*FUNCTION FROM SLIDE 22: http://web.fe.up.pt/~pfs/aulas/lcom2014/at/5kbrd.pdf*/
int kbc_output(unsigned long* data) {
	unsigned long stat;

	while( 1 ) {
		sys_inb(STAT_REG, &stat); /* assuming it returns OK */
		/* loop while 8042 output buffer is empty */
		if( stat & OBF ) {
			sys_inb(OUT_BUF, data); /* assuming it returns OK */
			if ( (stat &(PAR_ERR | TO_ERR)) == 0 )
				return *data;
			else
				return -1;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}

}


int kbd_test_scan(unsigned short ass) {
	timer_flag = 0;

	if(ass == 0) assembly_flag = 0;
	else assembly_flag = 1;

	receiver_loop();

	return 0;

}


int kbd_test_leds(unsigned short n, unsigned short *leds) {
	// 0 - scroll lock, 1 - numeric lock,  2 - caps lock

	int i, temp;
	printf("\n TESTE PARA VER SE OS PARAMETROS PASSARAM DIREITO \n");

	//	int resp=kbc_input(DATA_REG, cmd);
	//	if(resp != ACK)
	//		return resp;
	//	for(i = 0; i < tries; i++)
	//	{
	//		kbc_input(DATA_REG, cmd[1]);
	//		temp = kbc_output();
	//		if(aux == ACK || aux == Error || aux == -1)
	//			return aux;
	//
	//		delay(1);
	//	}
	//


	for(i=0; i < n; i++) {
		printf("LED: %lu \n", leds[i]);
	}

	keyboard_subscribe_int();

	//	if(sys_outb(OUT_BUF,0xED)) return 1;
	//kbc_output(0xED);
	//kbc_ouput(0x04);
	sleep(1);

	keyboard_unsubscribe_int();
	return 0;

}


int kbd_test_timed_scan(unsigned short n) {
	timer_flag = 1;
	time = n;
	receiver_loop();

}
