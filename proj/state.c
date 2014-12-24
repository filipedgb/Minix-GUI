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

int check_mouse_double_click(mouse_state current_mouse_state) {

	int index = getFolderByCoords(current_mouse_state.x,current_mouse_state.y);
	if(index != -1) {
		printf("double click no index %d", index);
		openFolder(index);
	}

}


void openFolder(int index) {


	getSubFolders(getFolderName(index));
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

char* getPath() {
	return current_path;
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


int isFile(char* path) {
	struct stat s;
	if( stat(path,&s) == 0 ) {
		if( s.st_mode & S_IFDIR ) return 0;
		else if( s.st_mode & S_IFREG ) return 1;
	}
}


int getSubFolders(char* foldername) {

	memset(currentFolders,0, 100);

	char temp[256];
	char old_path[1024];
	strcpy(temp,foldername);
	strcpy(old_path,current_path);


	printf("FOLDERNAME: %s\n",foldername);

	if(strcmp(temp,"") == 0) strcpy(current_path,".");

	else sprintf(current_path,"%s/%s",current_path,temp);

	printf("Current path: %s\n", current_path);


	if(isFile(current_path)) {
		strcpy(current_path,old_path);
		return 1;
	}

	num_folders = 0;

	struct dirent *de=NULL;
	DIR *d=NULL;

	d=opendir(current_path);
	if(d == NULL) {
		perror("Couldn't open directory");
		return(2);
	}
	int i = 0;
	// Loop while not NULL
	while(de = readdir(d)) {
		num_folders++;

		if(i > 50) break;

		if (strlen(de->d_name) > 0x20)
			printf("name too long: %s", de->d_name);

		else if(strlen(de->d_name) < 0x01)
			printf("name empty\n");


		else {

			printf("Folder %d name: %s\n",i,de->d_name);

			strcpy(	currentFolders[i].name, de->d_name);

		}
		i++;

	}

	closedir(d);
	return(0);

}
