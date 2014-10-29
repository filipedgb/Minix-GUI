#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <minix/syslib.h>
#include <minix/drivers.h>
#include "headers.h"
#include "i8254.h"
#include "timer.h"

static int hook_id_2 = 1; // variable for keyboard subscribes
static int timer_flag = 0; // if set to 1, timer interrupts will be enabled
static int assembly_flag = 0; // if set to 1, scan codes will be read using assembly code
static int time = 5; // time before the scanning times out
static int* leds_state; // array to keep the current state of the keyboard leds

/**
 * @brief To handle the keyboard interrupts
 *
 * Reads the codes from the output buffer
 *
 * @param code variable where they key scanned code is stored
 *
 * @return Return 0 upon success and non-zero otherwise
 */

int keyboard_int_handler_C(unsigned long *code);

/**
 * @brief Subscribes and enables keyboard interrupts
 *
 * @return Returns bit order in interrupt mask; negative value on failure
 */

int keyboard_subscribe_int();

/**
 * @brief Unsubscribes keyboard interrupts
 *
 * @return Return 0 upon success and non-zero otherwise
 */

int keyboard_unsubscribe_int();

/**
 * @brief Sends a command to the keyboard
 *
 * Reads the codes from the output buffer
 *
 * @param command Sends the command first
 * @param argument Then, if needed, sends the argument
 *
 * @return Return 0 upon success and non-zero otherwise
 */

int issue_command(unsigned long command, unsigned long argument);

/**
 * @brief Turn the leds on/off
 *
 * Creates the argument parameter, with bitmasks, to send to the keyboard
 *
 * @param n number of elements of the second argument
 * @param leds array with the LEDs to toggle (Ranges from 0 t0 2)
 *
 */

void process_leds(unsigned short n, unsigned short *leds);

/**
 * @brief Reset leds state to default
 */

void reset_leds();

/**
 * @brief Subscribes Timer 0 interrupts (if timer enabled) and keyboard interrupts
 *
 * Calls the respective handlers at each interrput
 *
 */

void receiver_loop();

/**
 * @brief Print scan codes
 *
 * @param code variable to be displayed on screen
 */

void print_codes(unsigned long code);

/**
 * FUNCTION FROM SLIDE 21: http://web.fe.up.pt/~pfs/aulas/lcom2014/at/5kbrd.pdf
 */

int kbc_input(char kbc_command);

/**
 * FUNCTION FROM SLIDE 22: http://web.fe.up.pt/~pfs/aulas/lcom2014/at/5kbrd.pdf
 */

int kbc_output(unsigned long* data);


#endif /* __KEYBOARD_H */
