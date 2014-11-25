#include "sprite.h"
#include "stdlib.h"
#include "video_gr.h"

char *initialize_sprite(char *xpm[], int * width2, int * height2) {

	Sprite *Sp = (Sprite *) malloc (sizeof(Sprite));

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

void draw_sprite(unsigned short xi, unsigned short yi, char *xpm[]) {

	int width, height;
	char *map;

	map = initialize_sprite(xpm, &width, &height);

	draw_map(xi,yi,width,height,map);
}
