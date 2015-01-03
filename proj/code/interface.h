#ifndef __INTERFACE_H
#define __INTERFACE_H

#include "pixmap.c"
#include "video_gr.h"
#include "mouse.h"
#include "logic.h"
#include "rtc.h"

/**
 * Centers an image on the screen
 *
 * @param imageWidth
 * @return
 */
int centerImageX(int imageWidth);

/**
 * Draws the initial interface (Penguin, logo and developers)
 */
void mainDraw() ;

/**
 * Draws the cursor on the screen according to mouse_state coordinates
 * @param current_mouse_state
 */
void drawCursor(mouse_state current_mouse_state);

/**
 * Draws the background
 */
void drawBackground();

/**
 * Erases the cursor from the screen according to mouse_state coordinates
 * @param current_mouse_state
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
 * @param title
 * @param message
 */
void drawInputBox(char* title, char* message);

/**
 * Draws a pop-up box with title and message
 * @param title
 * @param message
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
 *	Receives a string and draws it starting from  positionX and positionY coordinates
 * @param string
 * @param positionX
 * @param positionY
 */
void draw_string(char* string,int positionX,int positionY);

/**
 * Draws right click menu according to mouse_state coordinates
 * @param current_mouse_state
 */
void drawRightClickMenu(mouse_state current_mouse_state);



/**
 * Draws Clock according to its current state
 * @param current_rtc_state
 */
void drawClock(rtc_state current_rtc_state);

/**
 * Draws the folders and files on the screen
 */
void drawFolders();



#endif
