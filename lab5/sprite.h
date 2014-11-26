typedef struct {

	int x, y;
	int width, height;
	char *map;

} Sprite;

Sprite *initialize_sprite(char *xpm[], int * width2, int * height2);

void destroy_sprite(Sprite *Sp);
