#include "logic.h"
#include <stdio.h>
#include <stdlib.h>




int collision(mouse_state mouse, Button a) {
	if(mouse.x > a.xi && mouse.x < a.xf && mouse.y > a.yi && mouse.y < a.yf)
		return 1;

	return 0;
}





int check_mouse_click(mouse_state current_mouse_state) {

	if(isBox()) {
		if(collision(current_mouse_state,yesButton)) {
			currentBox.confirmed = 1;
			disableBox();
			return 4;

		}

		else if(collision(current_mouse_state,noButton)) {
			disableBox();
			return 5;

		}

		else return -1;
	}

	if(current_mouse_state.lb && collision(current_mouse_state,exitButton) ) {

		enableBox(1,"TURN OFF","Are you sure you want to turn off?");

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



void initButtons() {
	exitButton.xi = 0; exitButton.xf = 30;
	exitButton.yi = 0; 	exitButton.yf = 30;

	yesButton.xi = getHRES()/2-100; yesButton.xf = getHRES()/2-40;
	yesButton.yi = getVRES()/2+30; yesButton.yf = getVRES()/2+60;

	noButton.xi = getHRES()/2+50; noButton.xf = getHRES()/2 +110;
	noButton.yi = getVRES()/2+30; noButton.yf =getVRES()/2+60;
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


void check_rename_folder() {
	int i = 0;

	for(; i < num_folders; i++) {

		if(currentFolders[i].selected) {
			renameFolder(i);
		}

	}

	rename_flag = 0;
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

void setRenameFlag() {
	rename_flag = 1;
}

int getRenameFlag() {
	return rename_flag;
}


int isBoxConfirmed() {
	return currentBox.confirmed ;

}


void openFolder(int index) {
	getSubFolders(getFolderName(index));
}


void disableBox() {
	currentBox.active = 0;
	strcpy(currentBox.title,"");
	//strcpy(currentBox.text,"");

}

void enableBox(int type,char* title, char* text) {
	strcpy(currentBox.title,title);
	if(text != NULL) strcpy(currentBox.text,text);


	currentBox.active = 1;
	currentBox.output = type;
}

char* getBoxTitle(){
	return currentBox.title;
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

char* getTitle() {
	return currentBox.title;
}


void deleteFolder(int index) {
	char tempPath[1024];

	strcpy(tempPath,current_path);

	updatePath(getFolderName(index));

	remove(current_path);

	strcpy(current_path,tempPath);

	getSubFolders(current_path);
}

void renameFolder(int index) {
	char tempPath[1024];
	char old_name[1024];
	char new_name[1024];

	strcpy(tempPath,current_path); //copia do inicial

	updatePath(getFolderName(index)); // criar o path para o ficheiro que é suposto mudar de nome
	strcpy(old_name,current_path); // guardar o path do ficheiro que é para mudar de nome

	strcpy(current_path,tempPath);// voltar a por o path da pasta onde estamos
	sprintf(new_name,"%s%s%s",current_path,"/",currentBox.text);

	strcpy(current_path,tempPath);// voltar a por o path da pasta onde estamos

	printf("Old name: %s",old_name);
	printf("New name: %s",new_name);
	printf("Text Box: %s",currentBox.text);

	rename(old_name,new_name);

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

char getCharByNumber(unsigned long input)  {
	switch(input) {
	case 10: return 'a'; break;
	case 11: return 'b'; break;
	case 12: return 'c'; break;
	case 13: return 'd'; break;
	case 14: return 'e'; break;
	case 15: return 'f'; break;
	case 16: return 'g'; break;
	case 17: return 'h'; break;
	case 18: return 'i'; break;
	case 19: return 'j'; break;
	case 20: return 'k'; break;
	case 21: return 'l'; break;
	case 22: return 'm'; break;
	case 23: return 'n'; break;
	case 24: return 'o'; break;
	case 25: return 'p'; break;
	case 26: return 'q'; break;
	case 27: return 'r'; break;
	case 28: return 's'; break;
	case 29: return 't'; break;
	case 30: return 'u'; break;
	case 31: return 'v'; break;
	case 32: return 'w'; break;
	case 33: return 'x'; break;
	case 34: return 'y'; break;
	case 35: return 'z'; break;
	case 36: return ' '; break;

	}
}

void updateTextBox(unsigned long input) {
	char letter = getCharByNumber(input);
	char newText[50];
	sprintf(newText,"%s%c",currentBox.text,letter);
	strcpy(currentBox.text,newText);

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


			//printf("Folder %d name: %s\n",i,de->d_name);

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


//char *load_file(char *filePath) {
//
//	FILE *fileToLoad;
//	long fSize;
//	char *buffer;
//
//	fileToLoad = fopen(filePath, "r");
//	if (!fileToLoad) {
//		perror(filePath); exit(1);
//	}
//
//	fseek(fileToLoad, 0L, SEEK_END);
//	fSize = ftell(fileToLoad);
//	rewind(fileToLoad);
//
//	/*Allocating file mem*/
//	buffer = malloc(fSize + 1);
//	if (!buffer) {
//		fclose(fileToLoad);
//		perror("Mem alloc failed");
//	}
//
//	if (fread(buffer, fSize, 1, fileToLoad) != 1) {
//		fclose(fileToLoad);
//		free(buffer);
//		perror("Failed to read file");
//	}
//
//	fclose(fileToLoad);
//	return buffer;
//}
