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


void get_clock(rtc_state* current_clock_state) {

	unsigned long h,m,s,d,mth,y;

	wait_valid_rtc();
	sys_outb(RTC_ADDR_REG,HOURS_ADDR);
	sys_inb(RTC_DATA_REG,&h);

	sys_outb(RTC_ADDR_REG,MINUTES_ADDR);
	sys_inb(RTC_DATA_REG,&m);

	sys_outb(RTC_ADDR_REG,SECONDS_ADDR);
	sys_inb(RTC_DATA_REG,&s);

	sys_outb(RTC_ADDR_REG,DAY_ADDR);
	sys_inb(RTC_DATA_REG,&d);

	sys_outb(RTC_ADDR_REG,MONTH_ADDR);
	sys_inb(RTC_DATA_REG,&mth);

	sys_outb(RTC_ADDR_REG,YEAR_ADDR);
	sys_inb(RTC_DATA_REG,&y);

	if(h > 12) 	(*current_clock_state).hours = BCDToDecimal(h) -69;
	else (*current_clock_state).hours = BCDToDecimal(h);
	(*current_clock_state).minutes = BCDToDecimal(m);
	(*current_clock_state).seconds = BCDToDecimal(s);
	(*current_clock_state).day = BCDToDecimal(d);
	(*current_clock_state).month = BCDToDecimal(mth);
	(*current_clock_state).year = BCDToDecimal(y);



	//printf("H: %d, M: %d, S: %d \n",(*current_clock_state).hours, (*current_clock_state).minutes, (*current_clock_state).seconds);


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
	int mask = 0 | BIT(REG_B_PIE) | BIT(REG_B_AIE) | BIT(REG_B_UIE) ;
	char char_mask =(char) ( ~(mask) );


	sys_outb(RTC_DATA_REG, RTC_REG_B & char_mask);
}
