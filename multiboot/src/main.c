#include <stdint.h>
#include "include/multiboot.h"
#include "include/memory.h"
#include "include/print.h"
#include "include/vga.h"


static void qemu_gdb_hang(void)
{
#ifdef DEBUG
	static volatile int wait = 1;

	while (wait);
#endif
}


void main(void)
{
	qemu_gdb_hang();
	vga_clr();
	printf("Hello, World!\n");
}