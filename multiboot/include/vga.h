#ifndef __VGA_H__
#define __VGA_H__

#include <stddef.h>

void vga_write(const char *data, size_t size);
void vga_clr(void);

#endif /*__VGA_H__*/
