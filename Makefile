AS = nasm
CC = i686-elf-gcc
GRUB_MKRESCUE = i686-elf-grub-mkrescue

CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib

all: myos.iso

boot.o: boot.asm
	$(AS) -f elf32 boot.asm -o boot.o

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o

kernel.elf: boot.o kernel.o linker.ld
	$(CC) $(LDFLAGS) boot.o kernel.o -lgcc -o kernel.elf

myos.iso: kernel.elf grub.cfg
	mkdir -p isodir/boot/grub
	cp kernel.elf isodir/boot/kernel.elf
	cp grub.cfg isodir/boot/grub/grub.cfg
	$(GRUB_MKRESCUE) -o myos.iso isodir

run: myos.iso
	qemu-system-i386 -boot d -cdrom myos.iso -no-reboot -no-shutdown

clean:
	rm -rf *.o *.elf *.iso isodir
