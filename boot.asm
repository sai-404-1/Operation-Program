; boot.asm
; Стартовая точка ядра для GRUB Multiboot

bits 32

section .multiboot
align 4

MULTIBOOT_MAGIC equ 0x1BADB002
MULTIBOOT_FLAGS equ 0x00000003
MULTIBOOT_CHECKSUM equ -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

dd MULTIBOOT_MAGIC
dd MULTIBOOT_FLAGS
dd MULTIBOOT_CHECKSUM


section .bss
align 16

stack_bottom:
    resb 16384          ; 16 KiB stack
stack_top:


section .text
global _start
extern kernel_main

_start:
    ; Настраиваем стек для C-кода
    mov esp, stack_top

    ; GRUB передаёт:
    ; eax = magic number
    ; ebx = pointer to multiboot info
    ;
    ; Если kernel_main принимает аргументы:
    ; void kernel_main(uint32_t magic, uint32_t multiboot_info)
    ;
    ; Тогда можно передать их через стек:
    push ebx
    push eax
    call kernel_main

.hang:
    cli
    hlt
    jmp .hang