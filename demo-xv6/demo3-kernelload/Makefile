CC = gcc
AS = gas
LD = ld
OBJCOPY = objcopy
OBJDUMP = objdump

CFLAGS = -fno-pic -static -fno-builtin -fno-strict-aliasing -Wall -MD -ggdb -m32 -Werror -fno-omit-frame-pointer -g
CFLAGS += -fno-stack-protector
ASFLAGS = -m32 -gdwarf-2 -Wa,-divide
LDFLAGS += -melf_i386

kernel.img: bootblock kernel
	dd if=/dev/zero of=kernel.img count=10000
	dd if=bootblock of=kernel.img conv=notrunc
	dd if=kernel of=kernel.img seek=1 conv=notrunc

bootblock: bootasm.S bootmain.c
	${CC} ${CFLAGS} -fno-pic -O -nostdinc -I. -c bootmain.c
	$(CC) $(CFLAGS) -fno-pic -nostdinc -c bootasm.S
	$(LD) $(LDFLAGS) -N -e start -Ttext 0x7C00 -o bootblock.o bootasm.o bootmain.o
	$(OBJCOPY) -S -O binary -j .text bootblock.o bootblock
	./sign.pl bootblock

kernel: entry.o kernel.ld
	$(LD) $(LDFLAGS) -T kernel.ld -o kernel entry.o -b binary

qemu: kernel.img
	qemu-system-i386 -hda kernel.img -m 512m

clean:
	rm -f *.o *.d\
		bootblock kernel.img kernel
