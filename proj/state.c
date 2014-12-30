#include "state.h"
#include <stdio.h>
#include <stdlib.h>


int check_mouse_click(mouse_state current_mouse_state) {

	if(isBox()) {
		if(current_mouse_state.x > getHRES()/2 -100 && current_mouse_state.x < getHRES()/2 -40 &&
				current_mouse_state.y > getVRES()/2 + 30 && current_mouse_state.y < getVRES()/2 + 60) {
			currentBox.confirmed = 1;
			disableBox();
			return 4;

		}

		else if(current_mouse_state.x > getHRES()/2 +50 && current_mouse_state.x < getHRES()/2 +110 &&
				current_mouse_state.y > getVRES()/2 + 30 && current_mouse_state.y < getVRES()/2 + 60) {
			disableBox();
			return 5;

		}

		else return -1;
	}

	if(current_mouse_state.lb &&
			current_mouse_state.x < 30 && current_mouse_state.x > 0 &&
			current_mouse_state.y < 30 && current_mouse_state.y > 0) {

		enableBox(1,"Are you sure you want to turn off?");

		turn_off_flag = 1;

		return 1;
	}

	else if( current_mouse_state.lb) {
		int index = getFolderByCoords(current_mouse_state.x,current_mouse_state.y);

		if(index != -1) {
			toggleSelected(index);
			return 2; //index found
		}

	}

	else if(current_mouse_state.rb) {
		int index = getFolderByCoords(current_mouse_state.x,current_mouse_state.y);

		if(index != -1) {
			return 3; //index found
		}
	}

	return 0;

}


int check_mouse_double_click(mouse_state current_mouse_state) {

	int index = getFolderByCoords(current_mouse_state.x,current_mouse_state.y);
	if(index != -1) {
		printf("double click no index %d", index);
		openFolder(index);
		return 1;
	}

	return 0;

}


int check_delete_files() {
	int i = 0;

	for(; i < num_folders; i++) {

		if(currentFolders[i].selected) {
			deleteFolder(i);
		}

	}

	delete_flag = 0;


}

void setDeleteFlag() {
	delete_flag = 1;
}

int getDeleteFlag() {
	return delete_flag;
}

int getTurnOffFlag() {
	return turn_off_flag;
}

int isBoxConfirmed() {
	return currentBox.confirmed ;


}


void openFolder(int index) {
	getSubFolders(getFolderName(index));
}


void disableBox() {
	currentBox.active = 0;
}

void enableBox(int type,char* text) {
	strcpy(currentBox.text,text);
	currentBox.active = 1;
	currentBox.output = type;
}

char* getBoxText(){
	return currentBox.text;
}

int isBox() {
	return currentBox.active;
}

int isOutput() {
	return currentBox.output;
}


void deleteFolder(int index) {
	char tempPath[1024];

	strcpy(tempPath,current_path);

	updatePath(getFolderName(index));

	remove(current_path);

	strcpy(current_path,tempPath);

	getSubFolders(current_path);
}

int navigateLeft() {

	int folderSelected = getFolderSelected();

	if (folderSelected == -1) toggleSelected(0);

	if (folderSelected > 0) {
		toggleSelected(folderSelected);
		toggleSelected(folderSelected - 1);
	}
}

int navigateRight() {

	int folderSelected = getFolderSelected();
	int nFolders = getNumberFolders();

	if (folderSelected == -1) toggleSelected(0);

	if (folderSelected < nFolders && folderSelected > -1) {
		toggleSelected(folderSelected);
		toggleSelected(folderSelected + 1);
		}
}

int navigateUp() {

	int folderSelected = getFolderSelected();

	if (folderSelected == -1) toggleSelected(0);

	if (folderSelected > 10) {
		toggleSelected(folderSelected);
		toggleSelected(folderSelected - 10);
	}
}

int navigateDown() {

	int folderSelected = getFolderSelected();
	int nFolders = getNumberFolders();
	int folderToNavigate = folderSelected + 10;

	if (folderSelected == -1) toggleSelected(0);

	if (folderToNavigate <= nFolders) {
		toggleSelected(folderSelected);
		toggleSelected(folderSelected + 10);
	}
}

char* getFolderName(int index) {
	return currentFolders[index].name ;
}

int isFolderSelected(int index) {
	return currentFolders[index].selected;

}

int openFolderByEnter() {

	int index = getFolderSelected();
	openFolder(index);
}

int moveBack() {

	openFolder(1);
}

int getFolderSelected() {

	int i = 0;
	int nFolders = getNumberFolders();
	for (i; i < nFolders; i++) {
		if (currentFolders[i].selected == 1) return i;
	}

	return -1;
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

int isFileByIndex(int index) {
	return currentFolders[index].file ;
}




int isFile(char* path) {
	struct stat s;
	if( stat(path,&s) == 0 ) {
		if( s.st_mode & S_IFDIR ) return 0;
		else if( s.st_mode & S_IFREG ) return 1;
	}
}


void updatePath(char* foldername) {
	char temp[256];

	strcpy(temp,foldername);

	if(strcmp(temp,"") == 0) strcpy(current_path,".");

	else sprintf(current_path,"%s/%s",current_path,temp);

	printf("Current path: %s\n", current_path);


}


int getSubFolders(char* foldername) {

	memset(currentFolders,0, 100);

	char old_path[1024];
	strcpy(old_path,current_path);

	updatePath(foldername);

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
			currentFolders[i].selected = 0;


			printf("Folder %d name: %s\n",i,de->d_name);

			strcpy(	currentFolders[i].name, de->d_name);

			char parent_path[1024];
			strcpy(parent_path,current_path);

			updatePath(currentFolders[i].name);

			if(isFile(current_path)) {
				currentFolders[i].file = 1;
			} else {
				currentFolders[i].file = 0;
			}

			strcpy(current_path,parent_path);





		}
		i++;

	}

	closedir(d);
	return(0);

}
