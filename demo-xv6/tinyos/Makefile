.PHONY: all
all: system.img

OBJS := \
	main.o  \
	string.o  \
	console.o

CC = gcc
AS = gas
LD = ld
OBJCOPY = objcopy
OBJDUMP = objdump

XFLAGS = -m64 -DX64 -mcmodel=kernel -mtls-direct-seg-refs -mno-red-zone
#CFLAGS = -fno-pic -static -fno-builtin -fno-strict-aliasing 
CFLAGS = -fno-pic -static -fno-builtin -fno-strict-aliasing -Wall -Werror
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

kernel.elf: entry.o kernel.ld ${OBJS}
	$(LD) $(LDFLAGS) -T kernel.ld -o kernel.elf entry.o ${OBJS} -b binary

qemu: system.img
	qemu-system-x86_64 -smp 2 -hda system.img -m 512m -enable-kvm

clean:
	rm -f *.o *.d *.asm\
		bootblock kernel.elf system.img
