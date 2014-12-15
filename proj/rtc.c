#include "rtc.h"



int rtc_subscribe_int() {
	int temp = hook_id_4; //integer between 0 and 31
	sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE ,&hook_id_4); // returns a hook id that you can then use to enable and disable irqs.
	sys_irqenable(&hook_id_4);
	return temp;

}

int rtc_unsubscribe_int() {
	sys_irqdisable(&hook_id_4);
	if (sys_irqrmpolicy(&hook_id_4)!= OK) return 1;
	return 0;
}


void rtc_interrupt_handler(rtc_state* current_clock_state) {

	unsigned long h,m,s;

	wait_valid_rtc();
	sys_outb(RTC_ADDR_REG,HOURS_ADDR);
	sys_inb(RTC_DATA_REG,&h);

	sys_outb(RTC_ADDR_REG,MINUTES_ADDR);
	sys_inb(RTC_DATA_REG,&m);

	sys_outb(RTC_ADDR_REG,SECONDS_ADDR);
	sys_inb(RTC_DATA_REG,&s);

	printf("H: %d, M: %d, S: %d \n", BCDToDecimal(h), BCDToDecimal(m), BCDToDecimal(s));


}


/* http://www.edaboard.com/entry1086.html */
unsigned int BCDToDecimal (unsigned int bcdByte)
{
	return (((bcdByte & 0xF0) >> 4) * 10) + (bcdByte & 0x0F);
}



void wait_valid_rtc(void) {
	unsigned long regA = 0;
	do {
		disable();
		sys_outb(RTC_ADDR_REG, RTC_REG_A);
		sys_inb(RTC_DATA_REG, &regA);
		enable();
	} while ( regA & BIT(REG_A_UIP));
}


void enable() {
	sys_outb(RTC_ADDR_REG, RTC_REG_B);
	sys_outb(RTC_DATA_REG, ( BIT(REG_B_PIE) | BIT(REG_B_AIE) | BIT(REG_B_UIE)));

}

void disable() {
	sys_outb(RTC_ADDR_REG, RTC_REG_B);
	sys_outb(RTC_DATA_REG, (0 << REG_B_PIE | 0 << REG_B_AIE | 0 << REG_B_UIE));
}
