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
static int* leds_state;

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


int keyboard_int_handler_C(unsigned long *code) {
	printf("K\n");
	kbc_output(code); // corre a fun��o que l� o output do KBC
	if (*code == ESC_BREAK_CODE) return 1;
	//sys_inb(OUT_BUF,&code); // vai buscar o c�digo da tecla ao output buffer
	return 0;
}

void print_codes(unsigned long code) {
	if (code == ESC_BREAK_CODE) printf("Escape break code: %2x.\nTerminating...\n",code);

	else if(code >> 7 & 0x01 == 1)  { // se o bit mais significativo se encontra a 1, ent�o trata-se de um break code
		printf("Break code: %2x\n",code);
	}

	else printf("Make code: %2x\n", code); // otherwise � um make code

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

	unsigned long code;


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

					if(keyboard_int_handler_ASM(&code)) running = 0;
					else seconds = 0;

					print_codes(code);


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

int issue_command(unsigned long command, unsigned long argument) {
	// If you want to issue a command without argument, pass -1 as second parameter

	unsigned long stat;

	sys_outb(0x60, command);//send command
	sys_inb(OUT_BUF, &stat);//read ACK

	if (stat != 0xFA) {
		printf("STAT VALUE 0x%x , nerro a\n",stat);
		return 1;
	}

	if(argument != -1) {
		if (sys_outb(0x60, argument) != OK ) {
			printf("\nerro b\n");
			return 1;
		}

		sys_inb(OUT_BUF, &stat); //read ACK
		if (stat != 0xFA) {
			printf("\nerro c\n");
			return 1;
		}
	}

	return 0;

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

	// VERIFICA��ES DE INPUT
	int i;

	/* Imprime e verifica se os valores dos leds para toggle s�o todos validos */
	for(i=0; i < n; i++) {
		printf("LED: %lu \n",leds[i]);
		if( leds[i] > 2 ||  leds[i] < 0){
			printf("\nERROR: Leds values must range from 0 to 2\n");
			return 1;
		}
	}

	// FUN��O EM SI

	int leds_argument_cmd;
	leds_state = malloc(3*sizeof(int));
	for(i=0; i < 3; i++) leds_state[i] = 0;

	keyboard_subscribe_int();
	for(i=0; i < n; i++) {
		leds_argument_cmd = 1;
		leds_argument_cmd = leds_argument_cmd << leds[i];

		printf("ARGUMENT: 0x%x \n",leds_argument_cmd);


		if (issue_command(0xED,leds_argument_cmd) != 0) printf("\nerro 1\n");
		else {
			leds_state[leds[i]] = !leds_state[leds[i]]; // toggle led state (in the array of states) of the led indicated in leds array
		}

		//tickdelay(micros_to_ticks(DELAY_US));
		sleep(2);
	}

	issue_command(0xF6,-1);
	keyboard_unsubscribe_int();
	return 0;

}


int kbd_test_timed_scan(unsigned short n) {
	timer_flag = 1;
	time = n;
	receiver_loop();

}
