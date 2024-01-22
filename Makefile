# CONNERIE DE MAKE FILE

C_SOURCES = $(wildcard kernel/*.c)

OBJ = ${C_SOURCES:.c=.o}

CC = gcc
CFLAGS = -g -m32 -ffreestanding -fno-PIC -fno-stack-protector -nostartfiles -nodefaultlibs \
         -Wall -Wextra -Werror

e93-os.img: boot/bootsect.bin kernel.bin
	cat $^ > e93-os.bin
	dd if=/dev/zero bs=512 count=2880 >> $@
	dd if=e93-os.bin of=$@ conv=notrunc

kernel.bin: boot/kernel_entry.o ${OBJ}
	i686-linux-gnu-ld -no-pie -o $@ -Ttext 0x1000 $^ --oformat binary --allow-multiple-definition

run: e93-os.img
	qemu-system-i386 -fda $< -audiodev alsa,id=default -machine pcspk-audiodev=default

%.o: %.c ${C_HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -f *.bin *.img *.o *.bin *.o *.o *.o *.o *.o