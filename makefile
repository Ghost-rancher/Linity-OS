NASM=nasm
GCC=gcc
LD=ld
QEMU=qemu-system-i386
OUTPUT_DIR=files

all: clean build run
 
clean:
	rm -rf $(OUTPUT_DIR)/*
 
install:
	sudo apt-get install nasm gcc qemu
 
build: $(OUTPUT_DIR)/os-image.bin
 
run: build
	$(QEMU) -m 4G -fda $(OUTPUT_DIR)/os-image.bin > /dev/null 2>&1
 
$(OUTPUT_DIR)/os-image.bin: $(OUTPUT_DIR)/bootloader.bin $(OUTPUT_DIR)/kernel.bin
	cat $^ > $@
 
$(OUTPUT_DIR)/bootloader.bin: bootloader.asm
	$(NASM) $< -f bin -o $@
 
$(OUTPUT_DIR)/kernel-entry.o: kernel-entry.asm
	$(NASM) $< -f elf -o $@
 
$(OUTPUT_DIR)/kernel.o: kernel.c
	$(GCC) -m32 -ffreestanding -fno-builtin -nostdlib -c -fno-PIC $< -o $@
 
$(OUTPUT_DIR)/kernel.bin: $(OUTPUT_DIR)/kernel-entry.o $(OUTPUT_DIR)/kernel.o
	$(LD) -m elf_i386 -o $@ -Ttext 0x1000 -e _start $^ --oformat binary