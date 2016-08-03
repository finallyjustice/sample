.PHONY: all
all: system.img

OBJS := \
	main.o  \
	string.o  \
	console.o \
	spinlock.o \
	kalloc.o \
	vm64.o \
	acpi.o \
	mp.o \
	lapic.o

CC = gcc
AS = gas
LD = ld
OBJCOPY = objcopy
OBJDUMP = objdump

XFLAGS = -m64 -DX64 -mcmodel=kernel -mtls-direct-seg-refs -mno-red-zone
CFLAGS = -fno-pic -static -fno-builtin -fno-strict-aliasing 
#CFLAGS = -fno-pic -static -fno-builtin -fno-strict-aliasing -Wall -Werror
CFLAGS += -g -Wall -MD -fno-omit-frame-pointer
CFLAGS += -ffreestanding -fno-common -nostdlib -Iinclude -gdwarf-2 $(XFLAGS)
CFLAGS += $(call cc-option, -fno-stack-protector, "")
CFLAGS += $(call cc-option, -fno-stack-protector-all, "")
ASFLAGS = -gdwarf-2 -Wa,-divide -Iinclude $(XFLAGS)
LDFLAGS = -m elf_x86_64 -nodefaultlibs

system.img: bootblock kernel.elf
	dd if=/dev/zero of=system.img count=10000
	dd if=bootblock of=system.img conv=notrunc
	dd if=kernel.elf of=system.img seek=1 conv=notrunc

# bootblock is optimized for space
bootblock: bootasm.S bootmain.c
	$(CC) -fno-builtin -fno-pic -m32 -nostdinc -Iinclude -Os -o bootmain.o -c bootmain.c
	$(CC) -fno-builtin -fno-pic -m32 -nostdinc -Iinclude -o bootasm.o -c bootasm.S
	$(LD) -m elf_i386 -nodefaultlibs --omagic -e start -Ttext 0x7C00 \
		-o bootblock.o bootasm.o bootmain.o
	$(OBJDUMP) -S bootblock.o > bootblock.asm
	$(OBJCOPY) -S -O binary -j .text bootblock.o bootblock
	tools/sign.pl bootblock

entryother: entryother.S
	$(CC) $(CFLAGS) -fno-pic -nostdinc -I. -o entryother.o -c entryother.S
	$(LD) $(LDFLAGS) --omagic -e start -Ttext 0x7000 -o bootblockother.o entryother.o
	$(OBJCOPY) -S -O binary -j .text bootblockother.o entryother
	$(OBJDUMP) -S bootblockother.o > entryother.asm

kernel.elf: entry.o kernel.ld ${OBJS} entryother
	$(LD) $(LDFLAGS) -T kernel.ld -o kernel.elf entry.o ${OBJS} -b binary entryother
	$(OBJDUMP) -S kernel.elf > kernel.asm
	$(OBJDUMP) -t kernel.elf | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > kernel.sym

qemu: system.img
	qemu-system-x86_64 -smp 8 -hda system.img -m 1024m

clean:
	rm -f *.o *.d *.asm *.sym \
		bootblock entryother kernel.elf system.img
