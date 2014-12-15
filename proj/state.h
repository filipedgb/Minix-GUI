#ifndef __STATE_H
#define __STATE_H

#include "mouse.h"
#include <sys/types.h>
#include <dirent.h>

static int num_folders = 0;

typedef struct {
	int button_id;
	int xi;
	int xf;
	int yi;
	int yf;

} button;


typedef struct {

	char* name;
	int active;

} directory;

static directory currentFolders[30];


int getNumberFolders();


directory* getDirectories();
int getSubFolders(char* foldername,directory folders[30]);



int check_mouse_click(mouse_state current_mouse_state) ;



#endif
