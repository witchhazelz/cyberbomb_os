#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
	printf("'Sup kernel, I'm Cyberbomb!\n");
}
