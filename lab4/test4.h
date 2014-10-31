#ifndef __TEST4_H
#define __TEST4_H

/** @defgroup test4 test4
 * @{
 *
 * Functions for testing the kbd code
 */

/**
 * @brief To test packet reception via interrupts
 *
 * Displays the packets received from the mouse
 * Exits after receiving the number of packets received in argument
 *
 * @param cnt Number of packets to receive and display before exiting
 *
 * @return Return 0 upon success and non-zero otherwise
 */

int test_packet(unsigned short cnt);

/**
 * @brief To test handling of more than one interrupt
 *
 *  Similar test_packet() except that it
 *  should terminate if no packets are received for idle_time seconds
 *
 * @param idle_time Number of seconds without packets before exiting
 *
 * @return Return 0 upon success and non-zero otherwise
 */

int test_async(unsigned short idle_time);

/**
 * @brief To test reading and parsing of configuration
 *
 *  Reads mouse configuration and displays it in a human-friendly way
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int test_config(void);


/**
 * @brief To test state machine implementation
 *
 *  Similar test_packet() except that it
 *  should terminate if user moves the mouse continuously in one
 *    horizontal direction while pressing the left key down
 *
 * @param length minimum length of movement (mouse units).
 *  If positive, movement to the right, otherwise to the left.
 *
 * @param tolerance maximum movement (mouse units) on either vertical
 * 		direction required to consider a movement as "horizontal"
 *
 * @return Return 0 upon success and non-zero otherwise
 */


int test_gesture(short length, unsigned short tolerance);

#endif
