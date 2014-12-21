#include "state.h"



int check_mouse_click(mouse_state current_mouse_state) {

	if(current_mouse_state.lb &&
			current_mouse_state.x < 30 && current_mouse_state.x > 0 &&
			current_mouse_state.y < 30 && current_mouse_state.y > 0) {

		return 1;
	}

	else if( current_mouse_state.lb) {
		int index = getFolderByCoords(current_mouse_state.x,current_mouse_state.y);

		printf("Index found: %d\n", index);

		if(index != -1) toggleSelected(index);

	}

	return 0;


}


char* getFolderName(int index) {
	return currentFolders[index].name ;
}

int isFolderSelected(int index) {
	return currentFolders[index].selected;

}

void setFolderCoords(int index, int inX, int inY) {
	currentFolders[index].x = inX;
	currentFolders[index].y = inY;
}

void toggleSelected(int index) {
	if(currentFolders[index].selected == 1) currentFolders[index].selected = 0;
	else currentFolders[index].selected = 1;

}

Directory* getDirectories() {
	return currentFolders;
}

int getNumberFolders() {
	return num_folders;
}


int getFolderByCoords(int x, int y) {
	int k;
	for(k = 0; k < num_folders; k++){

		if(x > currentFolders[k].x && x < currentFolders[k].x + 36 && y > currentFolders[k].y &&  y < currentFolders[k].y+31) {
			return k;
		}

	}

	return -1;

}


int getSubFolders(char* foldername) {
	num_folders = 0;

	struct dirent *de=NULL;
	DIR *d=NULL;

	d=opendir(foldername);
	if(d == NULL) {
		perror("Couldn't open directory");
		return(2);
	}
	int i = 0;
	// Loop while not NULL
	while(de = readdir(d)) {
		num_folders++;
		Directory temp;
		strcpy(	currentFolders[i].name, de->d_name);
		i++;
	}

	closedir(d);
	return(0);

}
