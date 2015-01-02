#ifndef __STATE_H
#define __STATE_H

#include <minix/drivers.h>
#include "keyboard.h"
#include "read_xpm.h"
#include "timer.h"
#include "mouse.h"
#include "interface.h"
#include "rtc.h"
#include "video_gr.h"
#include "sprite.h"
#include "logic.h"


static char *background;

mouse_state current_mouse_state;

rtc_state current_rtc_state;

static int shift_mouse;
static int shift_keyboard;
static int shift_timer;


/**
 * Initiates program - Subscribes the devices used; Gets subfolders; Sets background and allocates necessary memory
 */
void init();

/**
 *
 */
int loop();

/**
 * Subscribe mouse, keyboard and timer
 */
void subscribe_devices();

/**
 * Unsubscribes mouse, keyboard and timer
 */
void unsubscribe_devices();

/**
 * Updates screen - Cleans screen, draws menus, folders, files and out/input boxes. Allocates necessary memory
 */
void updateScreen();

/**
 * Draws boot images
 */
void playIntro();

/**
 * Handles keyboard functionalities
 */
void kbc_consequences(int output);

/**
 * Handles keyboard functionalities
 */
void mouse_consequences(int output);





#endif
