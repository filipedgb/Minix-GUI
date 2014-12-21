#include "state.h"



int check_mouse_click(mouse_state current_mouse_state) {

	if(current_mouse_state.lb &&
			current_mouse_state.x < 30 && current_mouse_state.x > 0 &&
			current_mouse_state.y < 30 && current_mouse_state.y > 0) {

		return 1;
	}

	return 0;


}


char* getFolderName(int index) {
	return currentFolders[index].name ;
}



Directory* getDirectories() {
	return currentFolders;
}

int getNumberFolders() {
	return num_folders;
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
