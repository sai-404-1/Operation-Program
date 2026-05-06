AS = nasm
CC = i686-elf-gcc
GRUB_MKRESCUE = i686-elf-grub-mkrescue

CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib

all: myos.iso

boot.o: boot.asm
	$(AS) -f elf32 boot.asm -o boot.o

kernel.o: kernel/kernel.c
	$(CC) $(CFLAGS) -c kernel/kernel.c -o kernel.o

cpu.o: kernel/cpu.c
	$(CC) $(CFLAGS) -c kernel/cpu.c -o cpu.o

keyboard.o: kernel/keyboard.c
	$(CC) $(CFLAGS) -c kernel/keyboard.c -o keyboard.o

screen.o: kernel/screen.c
	$(CC) $(CFLAGS) -c kernel/screen.c -o screen.o

math.o: math.c
	$(CC) $(CFLAGS) -c math.c -o math.o

kernel.elf: boot.o math.o screen.o keyboard.o cpu.o kernel.o linker.ld
	$(CC) $(LDFLAGS) boot.o math.o screen.o keyboard.o cpu.o kernel.o -lgcc -o kernel.elf

myos.iso: kernel.elf grub.cfg
	mkdir -p isodir/boot/grub
	cp kernel.elf isodir/boot/kernel.elf
	cp grub.cfg isodir/boot/grub/grub.cfg
	$(GRUB_MKRESCUE) -o myos.iso isodir

run: myos.iso
	qemu-system-i386 -boot d -cdrom myos.iso \
	-drive file=other/38AEE764-2C55-464D-A9BD-511646A0932B.qcow2,format=qcow2,if=ide,index=0,media=disk
#  	-no-reboot -no-shutdown

clean:
	rm -rf *.o *.elf *.iso isodir
