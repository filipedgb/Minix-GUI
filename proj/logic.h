#ifndef __LOGIC_H
#define __LOGIC_H

#include "mouse.h"
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


static int num_folders = 0;

static char current_path[1024];

static int delete_flag;
static int turn_off_flag;

/**
 * Struct to handle buttons of the interface
 */
typedef struct Buttons {
	int button_id;
	int xi;
	int xf;
	int yi;
	int yf;

} Button;

/**
 * Struct to handle directories
 */
typedef struct Directories {
	char name[50];
	int file; //1 for file, 0 for folder
	int active;
	int selected;
	int x;
	int y;

} Directory;

/**
 * Struct to handle I/O boxes
 */
typedef struct ioboxes {
	char text[256];
	int output; //if 1 � output if 0 � input
	int active;
	int confirmed;

} iobox ;


static iobox currentBox;
static Button exitButton;
static Button yesButton;
static Button noButton;
Directory currentFolders[100];

/**
 * Handles mouse collisions
 */
int collision(mouse_state mouse, Button a);

/**
 * Handles mouse single click
 */
int check_mouse_click(mouse_state current_mouse_state);

/**
 * Initiates interface buttons
 */
void initButtons();

/**
 * Handles mouse double clicks
 */
int check_mouse_double_click(mouse_state current_mouse_state);

/**
 * Deletes selected folder/file
 */
int check_delete_files();

/**
 * Activates delete flag
 */
void setDeleteFlag();

/**
 * Returns delete flag
 */
int getDeleteFlag();

/**
 * Returns turn off flag
 */
int getTurnOffFlag();

/**
 * Returns whether a box is confirmed or not
 */
int isBoxConfirmed();

/**
 * Opens folder with a certain index
 */
void openFolder(int index);

/**
 * Disables box
 */
void disableBox();

/**
 * Enables box
 */
void enableBox(int type,char* text);

/**
 * Gets a box input
 */
char* getBoxText();

/**
 * Returns whether a box is active or not
 */
int isBox();

/**
 * Returns whether a box is out/input
 */
int isOutput();

/**
 * Deletes a folder with a certain index
 */
void deleteFolder(int index);

/**
 * Allows left arrow key navigation
 */
int navigateLeft();

/**
 * Allows right arrow key navigation
 */
int navigateRight();

/**
 * Allows up arrow key navigation
 */
int navigateUp();

/**
 * Allows down arrow key navigation
 */
int navigateDown();

/**
 * Returns a folder's name with a certain index
 */
char* getFolderName(int index);

/**
 * Returns whether a certain folder is selected or not
 */
int isFolderSelected(int index);

/**
 * Allows opening a folder by pressing Enter
 */
int openFolderByEnter();

/**
 * Returns to initial folder by pressing backspace
 */
int moveBack();

/**
 * Returns index of the folder currently selected
 */
int getFolderSelected();

/**
 * Sets folder coords
 */
void setFolderCoords(int index, int inX, int inY);

/**
 * Selects/Unselects a certain folder
 */
void toggleSelected(int index);

/**
 * Returns the current path
 */
char* getPath();

/**
 * Returns current folders of the current directory
 */
Directory* getDirectories();

/**
 * Returns the number of folders
 */
int getNumberFolders();

/**
 * Gets folder index by coordinates
 */
int getFolderByCoords(int x, int y);

/**
 * Returns whether it is a file or a folder by index
 */
int isFileByIndex(int index);

/**
 * Returns whether it is a file or a folder by path
 */
int isFile(char* path);

/**
 * Updates current path
 */
void updatePath(char* foldername);

/**
 * Gets a folder subfolders
 */
int getSubFolders(char* foldername);


#endif
