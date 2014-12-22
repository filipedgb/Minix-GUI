#include "interface.h"

void mainDraw() {

}


void drawCursor(mouse_state current_mouse_state) {
	draw_transp_sprite(current_mouse_state.x, current_mouse_state.y, cursor);
}


void drawBackground() {
	vg_fill(0x0);

}


void cleanCursor(mouse_state current_mouse_state) {
	draw_solid_rectangle(current_mouse_state.x,current_mouse_state.y,20,20,0);
}

void drawMainMenu() {

	draw_solid_rectangle(0,0,getHRES(),30,23) ;
	draw_solid_rectangle(0,0,30,30,20);

}


void cleanScreen() {
	vg_fill(0x00);

}

void draw_letter(char letter,int xIn,int yIn) {

	printf("letra actua: %c",letter);

	switch(letter) {
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



void drawClock(rtc_state current_rtc_state) {

	//printf("Chegou ao draw clock\n");

	//printf("H2: %d, M2: %d, S2: %d \n",current_rtc_state.hours, current_rtc_state.minutes, current_rtc_state.seconds);


	char final_string[256];

	char hours[10];
	char minutes[10];
	char seconds[10];

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

	sprintf(final_string,"%s  %s  %s",hours,minutes,seconds);

	//printf("Chegou ao fim");

	draw_string(final_string,getHRES()-200,15);

}


void drawFolders() {

	int k, altura = 30, posX = 30;

	for(k = 0; k < getNumberFolders(); k++) {
		if(k%10 == 0 && k > 0) {
			altura += 100;
			posX = 30;
		}
		else if(k > 0) posX += 90;

		setFolderCoords(k,posX + 30,50+altura);

		if(isFolderSelected(k))  draw_sprite(posX + 30, 50+altura, folder_selected);
		else draw_sprite(posX + 30, 50+altura, folder);

		char name[256];
		strcpy(name,getFolderName(k));
		printf("Passou aqui\n");
		printf("crashou no foldername, copia: %s original: %s\n",name,getFolderName(k));

		draw_string(getFolderName(k),posX + 35, 100+altura);
	}
}
