#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <minix/syslib.h>
#include <minix/drivers.h>
#include "headers.h"
#include "i8254.h"
#include "timer.h"

static int hook_id_2 = 1;
static int timer_flag = 0;
static int assembly_flag = 0;
static int time = 5;
static int* leds_state;


/**
 * Activate timer flag
 */
void setTimerFlag();

/**
 * Set seconds
 */
void setTime(int seconds);

/**
 * Handles interrupts for the keyboard
 */
int keyboard_int_handler_C(unsigned long *code);

/**
 * Subscribes keyboard interrupts
 */
int keyboard_subscribe_int();

/**
 * Unsubscribes keyboard interrupts
 */
int keyboard_unsubscribe_int();

/**
 *
 */
int issue_command(unsigned long command, unsigned long argument);

/**
 * Loop to handle keyboard interrupts
 */
int receiver_loop();

/**
 * Prints keyboard input codes
 */
void print_codes(unsigned long code);




#endif /* __KEYBOARD_H */
