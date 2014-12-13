#include "interface.h"

void mainDraw() {

}


void drawCursor(mouse_state current_mouse_state) {

	//draw_sprite(current_mouse_state.x, current_mouse_state.y, cursor);


	draw_rectangle(current_mouse_state.x,current_mouse_state.y,15,15,20);


}
