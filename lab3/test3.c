#include "test3.h"

int kbd_test_scan(unsigned short ass) {
	/* To be completed */
}
int kbd_test_leds(unsigned short n, unsigned short *leds) {
    /* To be completed */
}
int kbd_test_timed_scan(unsigned short n) {
    /* To be completed */
}

int keyboard_subscribe_int(void ) {
		int temp = hook_id; //integer between 0 and 31
        sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE ,&hook_id); // returns a hook id that you can then use to enable and disable irqs.
        sys_irqenable(&hook_id);
        return temp;
}

int timer_unsubscribe_int() {
        if (sys_irqrmpolicy(&hook_id)!= OK) return 1;
        return 0;
}
