CC ?= gcc
LD ?= ld
GDB ?= gdb

CFLAGS := -g -m64 -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -ffreestanding \
    -mcmodel=kernel -fno-pic -Wall -Wextra -Werror -pedantic -std=c99 \
    -Wframe-larger-than=1024 -Wstack-usage=1024 \
    -Wno-unknown-warning-option $(if $(DEBUG),-DDEBUG)
LFLAGS := -nostdlib -z max-page-size=0x1000

INC := ./include
SRC := ./src

C_SOURCES := $(shell find $(SRC) -name '*.c')
C_OBJECTS := $(C_SOURCES:%.c=%.o)
C_DEPS := $(C_SOURCES:%.c=%.d)

S_SOURCES := $(shell find $(SRC) -name '*.S')
S_OBJECTS := $(S_SOURCES:%.S=%.o)
S_DEPS := $(S_SOURCES:%.S=%.d)

OBJ := $(C_OBJECTS) $(S_OBJECTS)
DEP := $(C_DEPS) $(S_DEPS)

all: kernel

kernel: $(OBJ) kernel.ld
	$(LD) $(LFLAGS) -T kernel.ld -o kernel $(OBJ)

$(S_OBJECTS): %.o: %.S
	$(CC) -D__ASM_FILE__ -I$(INC) -g -MMD -c $< -o $@

$(C_OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) -I$(INC) -g -MMD -c $< -o $@

-include $(DEP)

.PHONY: start
start: all
	qemu-system-x86_64 -kernel kernel


.PHONY: clean
clean:
	rm -f kernel $(OBJ) $(DEP)


.PHONY: debug
debug: all
	qemu-system-x86_64 -kernel kernel -S -gdb tcp::1234


