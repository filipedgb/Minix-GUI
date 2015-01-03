typedef struct {

	int x, y;
	int width, height;
	char *map;

} Sprite;

/**
 * Initializes a sprite by allocating memory and reading it
 */
Sprite *initialize_sprite(char *xpm[], int * width2, int * height2);

/**
 * Deallocates the memory used by a certain sprite
 */
void destroy_sprite(Sprite *Sp);

/**
 * Draws a sprite
 */
void draw_sprite(unsigned short xi, unsigned short yi, char *xpm[]);

/**
 * Draws a transparent sprite
 */
void draw_transp_sprite(unsigned short xi, unsigned short yi, char *xpm[]);
