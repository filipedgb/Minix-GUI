#include "interface.h"

void mainDraw() {

}


void drawCursor(mouse_state current_mouse_state) {
	draw_sprite(current_mouse_state.x, current_mouse_state.y, cursor);
}



void cleanCursor(mouse_state current_mouse_state) {
	draw_rectangle(current_mouse_state.x-10,current_mouse_state.y-10,10,10,0);
}


void cleanScreen() {
	vg_fill(0x00);

}
