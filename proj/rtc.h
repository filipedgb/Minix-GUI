#ifndef __RTC_H
#define __RTC_H

#include "headers.h"
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include <minix/sysutil.h>

static int hook_id_4 = 3;


typedef struct {
	int seconds;
	int minutes;
	int hours;

} rtc_state;

unsigned int BCDToDecimal (unsigned int bcdByte);

void print_time();

void get_clock(rtc_state* current_clock_state);

void wait_valid_rtc(void);

void enable();

void disable();




#endif
