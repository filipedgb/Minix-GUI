#ifndef __INTERFACE_H
#define __INTERFACE_H

#include "pixmap.c"
#include "video_gr.h"
#include "mouse.h"
#include "logic.h"
#include "rtc.h"


void mainDraw() ;

void drawCursor(mouse_state current_mouse_state);

void drawBackground();

void cleanCursor(mouse_state current_mouse_state);

void drawMainMenu();

void cleanScreen();

void drawInputBox();

void drawOutputBox(char* message);

void draw_letter(char letter,int xIn,int yIn);

void drawFile(char *filePath);

void draw_string(char* string,int positionX,int positionY);

void drawRightClickMenu(mouse_state current_mouse_state);

void drawClock(rtc_state current_rtc_state);

void drawFolders();



#endif
