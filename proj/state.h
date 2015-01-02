#ifndef __STATE_H
#define __STATE_H

#include "keyboard.h"
#include "read_xpm.h"
#include "timer.h"
#include "mouse.h"
#include "interface.h"
#include "rtc.h"
#include "video_gr.h"
#include "sprite.h"
#include "logic.h"


#include <minix/drivers.h>




static char *background;

mouse_state current_mouse_state;

rtc_state current_rtc_state;

static int shift_mouse;
static int shift_keyboard;
static int shift_timer;




#endif
