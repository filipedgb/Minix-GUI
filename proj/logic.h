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


typedef struct Buttons {
	int button_id;
	int xi;
	int xf;
	int yi;
	int yf;

} Button;


typedef struct Directories {
	char name[50];
	int file; //1 for file, 0 for folder
	int active;
	int selected;
	int x;
	int y;

} Directory;


typedef struct ioboxes {
	char text[256];
	int output; //if 1 é output if 0 é input
	int active;
	int confirmed;

} iobox ;


static iobox currentBox;
static Button exitButton;
static Button yesButton;
static Button noButton;
Directory currentFolders[100];


int collision(mouse_state mouse, Button a);

int check_mouse_click(mouse_state current_mouse_state);

void initButtons();

int check_mouse_double_click(mouse_state current_mouse_state);

int check_delete_files();

void setDeleteFlag();

int getDeleteFlag();

int getTurnOffFlag();

int isBoxConfirmed();

void openFolder(int index);

void disableBox();

void enableBox(int type,char* text);

char* getBoxText();

int isBox();

int isOutput();

void deleteFolder(int index);

int navigateLeft();

int navigateRight();

int navigateUp();

int navigateDown();

char* getFolderName(int index);

int isFolderSelected(int index);

int openFolderByEnter();

int moveBack();

int getFolderSelected();

void setFolderCoords(int index, int inX, int inY);

void toggleSelected(int index);

char* getPath();

Directory* getDirectories();

int getNumberFolders();

int getFolderByCoords(int x, int y);

int isFileByIndex(int index);

int isFile(char* path);

void updatePath(char* foldername);

int getSubFolders(char* foldername);


#endif
