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


Directory currentFolders[100];

static iobox currentBox;



int getNumberFolders();
Directory* getDirectories();

int isFolderSelected(int index);

char* getFolderName(int index);

void openFolder(int index);

void deleteFolder(int index);

int getFolderByCoords(int x, int y);

char* getPath();

void toggleSelected(int index);

void setFolderCoords(int index, int inX, int inY);

void updatePath(char* foldername);

void setCurrentPath(char* path);

int getSubFolders(char* foldername);

int check_mouse_click(mouse_state current_mouse_state) ;



#endif
