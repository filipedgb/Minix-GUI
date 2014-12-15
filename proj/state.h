#ifndef __STATE_H
#define __STATE_H

#include "mouse.h"

typedef struct {
	int button_id;
	int xi;
	int xf;
	int yi;
	int yf;

} button;




int check_mouse_click(mouse_state current_mouse_state) ;



#endif
