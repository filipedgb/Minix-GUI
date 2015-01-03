#ifndef __RTC_H
#define __RTC_H

#include "headers.h"
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include <minix/sysutil.h>

static int hook_id_4 = 3;

/**
 * Struct to handle date and time
 */
typedef struct {
	int seconds;
	int minutes;
	int hours;
	int day;
	int month;
	int year;

} rtc_state;

/**
 * Converts BCD format into Decimal
 */
unsigned int BCDToDecimal (unsigned int bcdByte);

/**
 * Prints time
 */
void print_time();

/**
 * Gets computer clock
 */
void get_clock(rtc_state* current_clock_state);

/**
 * Validates time after changing hour
 */
void wait_valid_rtc(void);

/**
 * Enables RTC
 */
void enable();

/**
 * Disables RTC
 */
void disable();




#endif
