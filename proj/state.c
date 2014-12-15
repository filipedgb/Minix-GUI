#include "state.h"



int check_mouse_click(mouse_state current_mouse_state) {

	if(current_mouse_state.lb &&
			current_mouse_state.x < 30 && current_mouse_state.x > 0 &&
			current_mouse_state.y < 30 && current_mouse_state.y > 0) {

		return 1;
	}

	return 0;


}
