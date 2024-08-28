[bits 16]
[org 0x7c00]

mov si, welcome_msg
call print_string

kernel_offset equ 0x1000

mov [bootloader_drive_id], dl

mov bp, 0x9000
mov sp, bp

call kernel_loader

call switch_to_protected_mode

jmp $

[bits 16]
kernel_loader:
    mov bx, kernel_offset
    mov dh, 25
    mov dl, [bootloader_drive_id]
    call get_kernel_in_disk
    ret

[bits 32]
call_kernel:
    call kernel_offset
    jmp $

get_kernel_in_disk:
    pusha
    push dx

    mov ah, 0x02
    mov al, dh
    mov cl, 0x02
    mov ch, 0x00
    mov dh, 0x00

    int 0x13
    jc disk_error

    pop dx
    cmp al, dh
    jne sectors_error

    popa
    ret

disk_error:
    jmp disk_loop

sectors_error:
    jmp disk_loop

disk_loop:
    mov si, disk_error_msg
    call print_string
    jmp $


[bits 16]
switch_to_protected_mode:
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1 
    mov cr0, eax
    jmp CODE_SEG:init_protected_mode

[bits 32]
init_protected_mode:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    call call_kernel

print_string:       ; String yazdırma rutini
    lodsb          ; SI register'ındaki adresi al ve AL'ye yükle
    or al, al      ; AL'yi kontrol et, 0 ise son
    jz .done       ; Eğer 0 ise bitir
    mov ah, 0x0e   ; Teletype output
    int 0x10       ; Ekrana yaz
    jmp print_string
.done:
    ret

;;; gdt_start and gdt_end labels are used to compute size

; null segment descriptor
gdt_start:
    dq 0x0

; code segment descriptor
gdt_code:
    dw 0xffff    ; segment length, bits 0-15
    dw 0x0       ; segment base, bits 0-15
    db 0x0       ; segment base, bits 16-23
    db 10011010b ; flags (8 bits)
    db 11001111b ; flags (4 bits) + segment length, bits 16-19
    db 0x0       ; segment base, bits 24-31

; data segment descriptor
gdt_data:
    dw 0xffff    ; segment length, bits 0-15
    dw 0x0       ; segment base, bits 0-15
    db 0x0       ; segment base, bits 16-23
    db 10010010b ; flags (8 bits)
    db 11001111b ; flags (4 bits) + segment length, bits 16-19
    db 0x0       ; segment base, bits 24-31

gdt_end:

; GDT descriptor
gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; size (16 bit)
    dd gdt_start ; address (32 bit)

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

disk_error_msg db 'Disk Error', 0

bootloader_drive_id db 0

welcome_msg db 'Welcome to Linity Bootloader!', 0

; padding
times 510 - ($-$$) db 0

; magic number
dw 0xaa55