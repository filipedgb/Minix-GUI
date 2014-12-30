#include "interface.h"

void mainDraw() {
	draw_transp_sprite(405,200,logoM); //300
	draw_transp_sprite(435,201,logoI); // +30
	draw_transp_sprite(460,200,logoN); // +25
	draw_transp_sprite(488,201,logoI); // +17
	draw_transp_sprite(510,200,logoX); // +23
	draw_transp_sprite(560,200,logo3); // +39
	draw_transp_sprite(593,215,logoP); // +33
	draw_transp_sprite(605,200,logo1); // +12
	draw_transp_sprite(620,215,logoP); // +15
	draw_transp_sprite(634,200,logo8); // +14
	draw_transp_sprite(310,175,penguin);
}

void drawCursor(mouse_state current_mouse_state) {
	//printf("Chegou aqui no draw cursor\n");
	//printf("Mouse aqui x: %d , y: %d\n",current_mouse_state.x, current_mouse_state.y);
	draw_transp_sprite(current_mouse_state.x, current_mouse_state.y, cursor);
	//printf("Chegou aquitb\n");

}


void drawBackground() {
	vg_fill(0x0);

}


void cleanCursor(mouse_state current_mouse_state) {
	draw_solid_rectangle(current_mouse_state.x,current_mouse_state.y,20,20,0);
}

void drawMainMenu() {
	//printf("Chegou aqui no draw main menu\n");

	draw_solid_rectangle(0,0,getHRES(),30,23) ;
	draw_solid_rectangle(0,0,30,30,20);

	draw_transp_sprite(0,9,shutdown);

	//printf("Chegou aqui no draw main menu 2\n");


}

void cleanScreen() {
	vg_fill(0x00);

}

void drawInputBox() {
	draw_solid_rectangle(getHRES()/2 -250,getVRES()/2 -200,500,300,20);
	draw_rectangle(getHRES()/2 -248,getVRES()/2 -198,496,50,0);


	draw_rectangle(getHRES()/2 -200,getVRES()/2-50,400,25,0);
	draw_string("Type here:",getHRES()/2 -200,getVRES()/2-60);


	draw_rectangle(getHRES()/2 -100,getVRES()/2 + 30 ,60,30,0);
	draw_string("OK",getHRES()/2 -80,getVRES()/2 + 45);


	draw_rectangle(getHRES()/2 + 50,getVRES()/2 + 30 ,60,30,0);
	draw_string("CANCEL",getHRES()/2 +55,getVRES()/2 + 45);

	draw_string("TYPE IN THE BOX: ",getHRES()/2 -80,getVRES()/2 -170 );
}

void drawOutputBox(char* message) {
	draw_solid_rectangle(getHRES()/2 -250,getVRES()/2 -200,500,300,20);
	draw_rectangle(getHRES()/2 -248,getVRES()/2 -198,496,50,0);

	draw_rectangle(getHRES()/2 -100,getVRES()/2 + 30 ,60,30,0);
	draw_string("OK",getHRES()/2 -80,getVRES()/2 + 45);


	draw_rectangle(getHRES()/2 + 50,getVRES()/2 + 30 ,60,30,0);
	draw_string("CANCEL",getHRES()/2 +55,getVRES()/2 + 45);

	draw_string("MESSAGE: ",getHRES()/2 -50,getVRES()/2 -170 );
	draw_string(message,getHRES()/2 - 100,getVRES()/2 -50 );
}



void draw_letter(char letter,int xIn,int yIn) {

	printf("letra actua: %c",letter);

	switch(letter) {
	case ':':draw_transp_sprite(xIn,yIn,duplo_ponto); break;
	case '*':draw_transp_sprite(xIn,yIn,asterisc); break;
	case '/':draw_transp_sprite(xIn,yIn,barra); break;
	case '_':draw_transp_sprite(xIn,yIn,underscore); break;
	case ' ':draw_transp_sprite(xIn,yIn,space); break;
	case '.':draw_transp_sprite(xIn,yIn,ponto); break;
	case '0':draw_transp_sprite(xIn,yIn,xpm0); break;
	case '1':draw_transp_sprite(xIn,yIn,xpm1); break;
	case '2':draw_transp_sprite(xIn,yIn,xpm2); break;
	case '3':draw_transp_sprite(xIn,yIn,xpm3); break;
	case '4':draw_transp_sprite(xIn,yIn,xpm4); break;
	case '5':draw_transp_sprite(xIn,yIn,xpm5); break;
	case '6':draw_transp_sprite(xIn,yIn,xpm6); break;
	case '7':draw_transp_sprite(xIn,yIn,xpm7); break;
	case '8':draw_transp_sprite(xIn,yIn,xpm8); break;
	case '9':draw_transp_sprite(xIn,yIn,xpm9); break;

	case 'a': 	draw_transp_sprite(xIn,yIn,a);break;
	case 'b': 	draw_transp_sprite(xIn,yIn,b);break;
	case 'c': 	draw_transp_sprite(xIn,yIn,c);break;
	case 'd': 	draw_transp_sprite(xIn,yIn,d);break;
	case 'e': 	draw_transp_sprite(xIn,yIn,e);break;
	case 'f': 	draw_transp_sprite(xIn,yIn,f);break;
	case 'g': 	draw_transp_sprite(xIn,yIn,g);break;
	case 'h':	draw_transp_sprite(xIn,yIn,h);break;
	case 'i': 	draw_transp_sprite(xIn,yIn,i);break;
	case 'j': 	draw_transp_sprite(xIn,yIn,j);break;
	case 'k': 	draw_transp_sprite(xIn,yIn,k);break;
	case 'l': 	draw_transp_sprite(xIn,yIn,l);break;
	case 'm': 	draw_transp_sprite(xIn,yIn,m);break;
	case 'n': 	draw_transp_sprite(xIn,yIn,n);break;
	case 'o': 	draw_transp_sprite(xIn,yIn,o);break;
	case 'p': 	draw_transp_sprite(xIn,yIn,p);break;
	case 'q':	draw_transp_sprite(xIn,yIn,q);break;
	case 'r': 	draw_transp_sprite(xIn,yIn,r);break;
	case 's': 	draw_transp_sprite(xIn,yIn,s);break;
	case 't': 	draw_transp_sprite(xIn,yIn,t);break;
	case 'u': 	draw_transp_sprite(xIn,yIn,u);break;
	case 'v': 	draw_transp_sprite(xIn,yIn,v);break;
	case 'x':	draw_transp_sprite(xIn,yIn,x);break;
	case 'z': 	draw_transp_sprite(xIn,yIn,z);break;
	case 'y': 	draw_transp_sprite(xIn,yIn,y);break;
	case 'w': 	draw_transp_sprite(xIn,yIn,w);break;

	case 'A': 	draw_transp_sprite(xIn,yIn,a);break;
	case 'B': 	draw_transp_sprite(xIn,yIn,b);break;
	case 'C': 	draw_transp_sprite(xIn,yIn,c);break;
	case 'D': 	draw_transp_sprite(xIn,yIn,d);break;
	case 'E': 	draw_transp_sprite(xIn,yIn,e);break;
	case 'F': 	draw_transp_sprite(xIn,yIn,f);break;
	case 'G': 	draw_transp_sprite(xIn,yIn,g);break;
	case 'H':	draw_transp_sprite(xIn,yIn,h);break;
	case 'I': 	draw_transp_sprite(xIn,yIn,i);break;
	case 'J': 	draw_transp_sprite(xIn,yIn,j);break;
	case 'K': 	draw_transp_sprite(xIn,yIn,k);break;
	case 'L': 	draw_transp_sprite(xIn,yIn,l);break;
	case 'M': 	draw_transp_sprite(xIn,yIn,m);break;
	case 'N': 	draw_transp_sprite(xIn,yIn,n);break;
	case 'O': 	draw_transp_sprite(xIn,yIn,o);break;
	case 'P': 	draw_transp_sprite(xIn,yIn,p);break;
	case 'Q':	draw_transp_sprite(xIn,yIn,q);break;
	case 'R': 	draw_transp_sprite(xIn,yIn,r);break;
	case 'S': 	draw_transp_sprite(xIn,yIn,s);break;
	case 'T': 	draw_transp_sprite(xIn,yIn,t);break;
	case 'U': 	draw_transp_sprite(xIn,yIn,u);break;
	case 'V': 	draw_transp_sprite(xIn,yIn,v);break;
	case 'X':	draw_transp_sprite(xIn,yIn,x);break;
	case 'Z': 	draw_transp_sprite(xIn,yIn,z);break;
	case 'Y': 	draw_transp_sprite(xIn,yIn,y);break;
	case 'W': 	draw_transp_sprite(xIn,yIn,w);break;


	};

}

char *load_file(char *filePath) {

	FILE *fileToLoad;
	long fSize;
	char *buffer;

	fileToLoad = fopen(filePath, "r");
	if (!fileToLoad) {
		perror(filePath); exit(1);
	}

	fseek(fileToLoad, 0L, SEEK_END);
	fSize = ftell(fileToLoad);
	rewind(fileToLoad);

	/*Allocating file mem*/
	buffer = malloc(fSize + 1);
	if (!buffer) {
		fclose(fileToLoad);
		perror("Mem alloc failed");
	}

	if (fread(buffer, fSize, 1, fileToLoad) != 1) {
		fclose(fileToLoad);
		free(buffer);
		perror("Failed to read file");
	}

	fclose(fileToLoad);
	return buffer;
}

void drawFile(char *filePath) {

	char *buffer = load_file(filePath);
	int i = 0, x = 0, y = 0;

	while(buffer[i] != '\0') {

		if (buffer[i] == '\n') y++;

		//Fazer verificacao para x > screenWidth

		draw_letter(buffer[i], x, y);
		x++;
	}
}

void draw_string(char* string,int positionX,int positionY)  {
	int i = 0;

	int x = positionX;
	int y = positionY;

	printf("Tamanho no draw-string: %d\n",strlen(string));
	printf("String no draw-string: %s\n",string);


	for(i = 0; i < strlen(string); i++) {
		draw_letter(string[i],x,y);
		x += 8;

	}
}

void drawRightClickMenu(mouse_state current_mouse_state) {

	draw_solid_rectangle(current_mouse_state.x,current_mouse_state.y,80,90,20);

	draw_rectangle(current_mouse_state.x,current_mouse_state.y,80,30,0);
	draw_string("Cut",current_mouse_state.x+15,current_mouse_state.y+15);

	draw_rectangle(current_mouse_state.x,current_mouse_state.y+30,80,30,0);
	draw_string("Copy",current_mouse_state.x+15,current_mouse_state.y+45);

	draw_rectangle(current_mouse_state.x,current_mouse_state.y+60,80,30,0);
	draw_string("Paste",current_mouse_state.x+15,current_mouse_state.y+75);



}



void drawClock(rtc_state current_rtc_state) {

	//printf("Chegou ao draw clock\n");

	//printf("H2: %d, M2: %d, S2: %d \n",current_rtc_state.hours, current_rtc_state.minutes, current_rtc_state.seconds);


	char final_string[256];
	char final_string_date[256];

	char hours[10];
	char minutes[10];
	char seconds[10];
	char day[10];
	char month[10];
	char year[10];

	//printf("Teste das horas: %d",current_rtc_state.hours  );

	if(current_rtc_state.hours < 10) {
		sprintf(hours,"0%d",current_rtc_state.hours);
	} else sprintf(hours,"%d",current_rtc_state.hours);

	//printf("Horas %s:", hours);

	if(current_rtc_state.minutes < 10) {
		sprintf(minutes,"0%d",current_rtc_state.minutes);
	} else sprintf(minutes,"%d",current_rtc_state.minutes);

	if(current_rtc_state.seconds < 10) {
		sprintf(seconds,"0%d",current_rtc_state.seconds);
	} else sprintf(seconds,"%d",current_rtc_state.seconds);

	sprintf(final_string,"%s:%s:%s",hours,minutes,seconds);


	sprintf(final_string_date,"%d/%d/%d",current_rtc_state.day,current_rtc_state.month,current_rtc_state.year);


	//printf("Chegou ao fim");

	draw_string(final_string,getHRES()-100,10);
	draw_string(final_string_date,getHRES()-100,20);


}


void drawFolders() {

	int k, altura = 30, posX = 30;

	char path[1024];
	sprintf(path,"%s/%s","Current path: ",getPath());

	draw_string(path,posX+30,altura+25);
	draw_rectangle(posX+25,altura+20,getHRES()-150,15,20);
	draw_rectangle(posX+25,altura+20,posX+25+55,15,20);


	for(k = 0; k < getNumberFolders(); k++) {
		if(k%10 == 0 && k > 0) {
			altura += 100;
			posX = 30;
		}
		else if(k > 0) posX += 90;

		setFolderCoords(k,posX + 30,50+altura);

		//cleanScreen(), drawFile(path);
		//draw_sprite(posX + 30, 50+altura, document_selected);
		if(isFolderSelected(k) && isFileByIndex(k) ) {
			draw_sprite(posX + 30, 50+altura, document_selected);

			draw_string(getFolderName(k),posX + 35, 100+altura);

		}


		else if(isFolderSelected(k)) {
			draw_sprite(posX + 30, 50+altura, folder_selected);
			draw_string(getFolderName(k),posX + 35, 100+altura);

		}

		else if(isFileByIndex(k)) {
			draw_sprite(posX + 30, 50+altura, document);
			char name[5], name_cortado[6];
			strcpy(name,getFolderName(k));
			name[6] = 0;

			if( strlen(getFolderName(k)) > strlen(name)) {
				sprintf(name_cortado,"%s*",name);
				draw_string(name_cortado,posX + 35, 100+altura);
			} else {
				draw_string(name,posX + 35, 100+altura);

			}
		}


		else {
			draw_sprite(posX + 30, 50+altura, folder);
			char name[5], name_cortado[6];
			strcpy(name,getFolderName(k));
			name[6] = 0;

			if( strlen(getFolderName(k)) > strlen(name)) {
				sprintf(name_cortado,"%s*",name);
				draw_string(name_cortado,posX + 35, 100+altura);
			} else {
				draw_string(name,posX + 35, 100+altura);

			}
		}


	}
}
