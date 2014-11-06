#ifndef __MOUSE_H
#define __MOUSE_H

#include <minix/syslib.h>
#include <minix/drivers.h>
#include "headers.h"

static int hook_id_3 = 1;
static int timer_flag = 0;
static int time = 5;

int keyboard_int_handler();

int keyboard_subscribe_int();

int keyboard_unsubscribe_int();

int issue_command(unsigned long command, unsigned long argument);

void receiver_loop();

int kbc_input(char kbc_command);

int kbc_output(unsigned long* data);


#endif /* __KEYBOARD_H */
