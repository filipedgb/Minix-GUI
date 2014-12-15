#ifndef __INTERFACE_H
#define __INTERFACE_H

#include "pixmap.c"
#include "video_gr.h"
#include "mouse.h"

void mainDraw();

void drawCursor(mouse_state current_mouse_state);

void cleanScreen();

void drawMainMenu();


#endif
