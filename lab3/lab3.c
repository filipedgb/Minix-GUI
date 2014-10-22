#include "test3.h"
#include <minix/syslib.h>
#include <minix/drivers.h>



int main () {

	sef_startup();

	/* Enable IO-sensitive operations for ourselves */
	//sys_iopenable(SELF);

	kbd_test_scan(0);

	return 0;

}
