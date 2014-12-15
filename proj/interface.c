#include "interface.h"

void mainDraw() {

}


void drawCursor(mouse_state current_mouse_state) {
	draw_sprite(current_mouse_state.x, current_mouse_state.y, cursor);
}


void drawBackground() {
	vg_fill(0x0);
	drawFolders();

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

void drawFolders() {
	int i = 0;
	for(; i < 10; i++) {
		draw_sprite(i*60 + 30, 50, folder);

	}


}
