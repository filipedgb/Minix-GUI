#include "keyboard.h"

void setTimerFlag() {
	timer_flag = 1;
}

void setAssemblyFlag() {
	assembly_flag = 1;
}

void setTime(int seconds) {
	time = seconds;
}

int keyboard_subscribe_int(void ) {
	int temp = hook_id_2; //integer between 0 and 31
	sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE ,&hook_id_2); // returns a hook id that you can then use to enable and disable irqs.
	sys_irqenable(&hook_id_2);
	return temp;
}

int keyboard_unsubscribe_int() {
	sys_irqdisable(&hook_id_2);
	if (sys_irqrmpolicy(&hook_id_2)!= OK) return 1;
	return 0;
}


int keyboard_int_handler_C(unsigned long *code) {
	//printf("*This is the C handler*  ");
	//kbc_output(code); // corre a fun��o que l� o output do KBC

	sys_inb(OUT_BUF,code); // vai buscar o c�digo da tecla ao output buffer

	if (*code == ESC_BREAK_CODE) return 1;
	else if(*code == DELETE_MAKE_CODE) return 2;
	else if(*code == LEFT_ARROW_MAKE_CODE) return 3;
	else if(*code == RIGHT_ARROW_MAKE_CODE) return 4;

	return 0;
}



void print_codes(unsigned long code) {
	if (code == ESC_BREAK_CODE) printf("Escape break code: %2x.\nTerminating...\n",code);

	else if(code >> 7 & 0x01 == 1)  { // se o bit mais significativo se encontra a 1, ent�o trata-se de um break code
		printf("Break code: %2x\n",code);
	}

	else printf("Make code: %2x\n", code); // otherwise � um make code

}


int receiver_loop(int shiftkeyboard) {
	int ipc_status,r, seconds = 0, running = 1;
	message msg;

//	int shift_timer;
//	if(timer_flag) shift_timer = timer_subscribe_int();

	unsigned long code;


	while(running) {
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
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	return 1;


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
