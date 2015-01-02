#ifndef __INTERFACE_H
#define __INTERFACE_H

#include "pixmap.c"
#include "video_gr.h"
#include "mouse.h"
#include "logic.h"
#include "rtc.h"

/**
 * Centers an image on the screen
 */
int centerImageX(int imageWidth);

/**
 * Draws the initial interface (Penguin, logo and developers)
 */
void mainDraw() ;

/**
 * Draws the cursor on the screen
 */
void drawCursor(mouse_state current_mouse_state);

/**
 * Draws the background
 */
void drawBackground();

/**
 * Cleans the cursor
 */
void cleanCursor(mouse_state current_mouse_state);

/**
 * Draws main menu
 */
void drawMainMenu();

/**
 * Cleans the screen
 */
void cleanScreen();

/**
 * Draws input box for rename purposes
 */
void drawInputBox(char* title, char* message);

/**
 * Draws pop out messages
 */
void drawOutputBox(char* title, char* message);

/**
 * Draws letters
 */
void draw_letter(char letter,int xIn,int yIn);

/**
 * Draws file to the screen (not fully working)
 */
void drawFile(char *filePath);

/**
 * Draws a string to the screen
 */
void draw_string(char* string,int positionX,int positionY);

/**
 * Draws right click menu
 */
void drawRightClickMenu(mouse_state current_mouse_state);

/**
 * Draws RTC
 */
void drawClock(rtc_state current_rtc_state);

/**
 * Draws the folders and files on the screen
 */
void drawFolders();



#endif
