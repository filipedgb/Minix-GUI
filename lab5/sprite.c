#include "sprite.h"
#include "stdlib.h"
#include "video_gr.h"

char *initialize_sprite(char *xpm[], int * width2, int * height2) {

	Sprite *Sp = (Sprite *) malloc ( sizeof(Sprite));

	if (Sp == NULL) return NULL;

	char *mapb;
	mapb = read_xpm(xpm, width2, height2);

	if (mapb == NULL) {free(Sp); return NULL;}

	Sp->map = mapb;

	return Sp->map; //Assigning sprite's map
}

void destroy_sprite(Sprite *Sp, char *base) {

	if (Sp == NULL) return;

	free(Sp->map);
	free(Sp);

	Sp = NULL; // hopeless: pointer is passed by value
}

int animate_sprite() {

	Sprite *Sp;
}

