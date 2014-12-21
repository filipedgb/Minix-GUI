#ifndef __STATE_H
#define __STATE_H

#include "mouse.h"
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>


static int num_folders = 0;

static char current_path[1024];


typedef struct Buttons {
	int button_id;
	int xi;
	int xf;
	int yi;
	int yf;

} Button;


typedef struct Directories {
	char name[256];
	int active;
	int selected;
	int x;
	int y;

} Directory;

Directory currentFolders[30];


int getNumberFolders();
Directory* getDirectories();

int isFolderSelected(int index);

char* getFolderName(int index);

int getFolderByCoords(int x, int y);

char* getPath();

void toggleSelected(int index);

void setFolderCoords(int index, int inX, int inY);

void setCurrentPath(char* path);

int getSubFolders(char* foldername);

int check_mouse_click(mouse_state current_mouse_state) ;



#endif
