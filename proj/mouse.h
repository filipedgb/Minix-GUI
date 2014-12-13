#ifndef __MOUSE_H
#define __MOUSE_H

#include <minix/syslib.h>
#include <minix/drivers.h>
#include "headers.h"
#include "timer.h"
#include "video_gr.h"


static int hook_id_3 = 2;
static int tempo = 5;

typedef struct {
	int x;
	int y;
	int lb;
	int rb;
	int mb;
} mouse_state;

void setTolerance(int val);

void setLength(int val);

void setGesture();

void setMaxPackets(int max);

void print_packet();

void read_config();

void print_mouse_config();

int gesture_state_machine();


int mouse_int_handler();

int mouse_subscribe_int();

int mouse_unsubscribe_int();

int issue_command_mouse(unsigned char command, unsigned char argument);

void interruption_loop();

int kbc_input(char kbc_command);

int kbc_output();


#endif /* __KEYBOARD_H */
