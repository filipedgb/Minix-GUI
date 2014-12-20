#ifndef __STATE_H
#define __STATE_H

#include "mouse.h"
#include <sys/types.h>
#include <dirent.h>

static int num_folders = 0;

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

} Directory;

Directory currentFolders[30];


int getNumberFolders();
Directory* getDirectories();


char* getFolderName(int index);


int getSubFolders(char* foldername);
int check_mouse_click(mouse_state current_mouse_state) ;



#endif
