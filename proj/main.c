
#include <minix/drivers.h>

#include "state.h"

int main(int argc, char **argv) {

	/* Initialize service */
	sef_startup();

	minixBootAnimation(1);
	init();

	if(loop()) unsubscribe_devices();
	return 0;
}


