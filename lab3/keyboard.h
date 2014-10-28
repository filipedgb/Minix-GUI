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

int keyboard_int_handler_C(unsigned long *code);

int keyboard_subscribe_int();

int keyboard_unsubscribe_int();

int issue_command(unsigned long command, unsigned long argument);

void process_leds(unsigned short n, unsigned short *leds);

void reset_leds();

void receiver_loop();

void print_codes(unsigned long code);

int kbc_input(char kbc_command);

int kbc_output(unsigned long* data);


#endif /* __KEYBOARD_H */
