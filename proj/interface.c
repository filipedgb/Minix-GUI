#include "interface.h"

void mainDraw() {

}


void drawCursor(mouse_state current_mouse_state) {
	draw_sprite(current_mouse_state.x, current_mouse_state.y, a);
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

void draw_letter(char letter,int x,int y) {
	char **letra;

	printf("Letra que chega ao draw_letter: %c\n",letter);

	switch(letter) {
	case ' ': letra = space; break;
	case '.': letra = ponto; break;
	case '0': letra = xpm0; break;
	case '1': letra = xpm1; break;
	case '2': letra = xpm2; break;
	case '3': letra = xpm3; break;
	case '4': letra = xpm4; break;
	case '5': letra = xpm5; break;
	case '6': letra = xpm6; break;
	case '7': letra = xpm7; break;
	case '8': letra = xpm8; break;
	case '9': letra = xpm9; break;

	case 'a': letra = a; break;
	case 'b': letra = b; break;
	case 'c': letra = c; break;
	case 'd': letra = d; break;
	case 'e': letra = e; break;
	case 'f': letra = f; break;
	case 'g': letra = g; break;
	case 'h': letra = h; break;
	case 'i': letra = i; break;
	case 'j': letra = j; break;
	case 'k': letra = k; break;
	case 'l': letra = l; break;
	case 'm': letra = m; break;
	case 'n': letra = n; break;
	case 'o': letra = o; break;
	case 'p': letra = p; break;
	case 'q': letra = q; break;
	case 'r': letra = r; break;
	case 's': letra = s; break;
	case 't': letra = t; break;
	case 'u': letra = u; break;
	case 'v': letra = v; break;
	case 'x': letra = x; break;
	case 'z': letra = z; break;
	case 'y': letra = y; break;
	case 'w': letra = w; break;


	};

	draw_sprite(x,y,letra);
}


void draw_string(char* string,int positionX,int positionY)  {
	int i = 0;

	int x = positionX;
	int y = positionY;

	for(i = 0; i < strlen(string); i++) {
		draw_letter(string[i],x,y);
		x += 8;

	}
}


void drawFolders() {

	getSubFolders(".");

	int k;

	for(k = 0; k < getNumberFolders(); k++) {
		draw_sprite(k*60 + 30, 50, folder);
		char* name = getFolderName(k);
		draw_string(name,k*60 + 35, 100);
	}
}
