# SPDX-License-Identifier: GPL-3.0
#
# Maintained by: 
#   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
#
# This file is arch x86_64's main mk file.

TOOLCHAIN_PREFIX ?=
CC      = $(TOOLCHAIN_PREFIX)gcc
LD      = $(TOOLCHAIN_PREFIX)ld
OBJCOPY = $(TOOLCHAIN_PREFIX)objcopy
NASM    = nasm
QEMU    = qemu-system-x86_64
XORRISO = xorriso

ISO		= Linity_OS.iso
ISO_DIR	= iso
LIMINE_BINARY_DIR = toolchain/limine-binary
LIMINE	= $(LIMINE_BINARY_DIR)/limine

LD_FILE	= arch/$(ARCH)/kernel.ld
KERNEL_$(ARCH) 	= build/kernel/core/kernel.bin

REQUIRED_BINS := $(CC) $(LD) $(OBJCOPY) $(NASM) $(QEMU) $(XORRISO) tar curl

ARCH_CFLAGS		= -Iarch/$(ARCH) -Iinclude/arch/$(ARCH) -Iinclude/kernel
KERNEL_CFLAGS	= -Iinclude/kernel

COMMON_CFLAGS  = -m64 -mcmodel=kernel -mgeneral-regs-only
COMMON_CFLAGS += -ffreestanding -fno-builtin -nostdlib
COMMON_CFLAGS += -fno-PIC -fno-stack-protector -fno-stack-check -fno-omit-frame-pointer
COMMON_CFLAGS += -mno-sse -mno-sse2 -mno-mmx -mno-80387 -mno-red-zone
COMMON_CFLAGS += -Wall -Wmissing-prototypes -Wmissing-declarations
COMMON_CFLAGS += -O0 -g -fdiagnostics-color=always
COMMON_CFLAGS += -MMD -MP

LDFLAGS = -m elf_x86_64 -T $(LD_FILE) -z noexecstack
ASMFLAGS = -f elf64 -g

XORRISOFLAGS  = -as mkisofs -R -r -J
XORRISOFLAGS += -b boot/limine/limine-bios-cd.bin
XORRISOFLAGS += -no-emul-boot -boot-load-size 4 -boot-info-table
XORRISOFLAGS += >/dev/null 2>&1

QEMUFLAGS  = -m 4G -cpu host,+invtsc -enable-kvm
QEMUFLAGS += -cdrom $(ISO)
QEMUFLAGS += -vga virtio -serial stdio -display none

include arch/$(ARCH)/boot/makefile
include arch/$(ARCH)/hal/makefile

build/kernel/%.o: kernel/%.c
	$(call run_and_log,$<,$@,$(CC) $(COMMON_CFLAGS) $(KERNEL_CFLAGS) -c $< -o $@)

build/arch/%.o: arch/%.c
	$(call run_and_log,$<,$@,$(CC) $(COMMON_CFLAGS) $(ARCH_CFLAGS) -c $< -o $@)

build/kernel/%.asm.o: %.asm
	$(call run_and_log,$<,$@,$(NASM) $(ASMFLAGS) $< -o $@)

build/arch/%.asm.o: %.asm
	$(call run_and_log,$<,$@,$(NASM) $(ASMFLAGS) $< -o $@)

$(KERNEL_$(ARCH)):
	$(call run_and_log,[LD] Linking Kernel,$@,$(LD) $(LDFLAGS) -o $@ $^)
	@$(OBJCOPY) --only-keep-debug $@ build/kernel/core/kernel.sym

iso_$(ARCH): limine

limine: $(KERNEL_$(ARCH)) $(LIMINE)
	@mkdir -p $(ISO_DIR)/boot/limine
	@cp $(KERNEL_$(ARCH)) $(ISO_DIR)/boot/
	@cp boot/$(ARCH)/limine/limine.conf \
		$(LIMINE_BINARY_DIR)/limine-bios.sys \
		$(LIMINE_BINARY_DIR)/limine-bios-cd.bin \
		$(ISO_DIR)/boot/limine/
	$(call run_and_log,[XORRISO] Creating ISO Image,$(ISO),$(XORRISO) $(XORRISOFLAGS) $(ISO_DIR) -o $(ISO))
	$(call run_and_log,[LIMINE] Installing BIOS Boot Sectors,$(ISO),$(LIMINE) bios-install $(ISO))

run_$(ARCH):
	$(QEMU) $(QEMUFLAGS)

doctor:
	@$(foreach bin,$(REQUIRED_BINS), \
		command -v $(bin) >/dev/null 2>&1 || { printf '$(COLOR_RED)[X] "$(bin)" not found.$(COLOR_RESET)\n'; exit 1; }; \
	)
	@printf "$(COLOR_GREEN)[CHECK] Your system is ready to build Linity-OS.$(COLOR_RESET)\n"

$(LIMINE):
	@printf "\r\033[K$(COLOR_YELLOW)[CHECK] Downloading Limine... [WARN]$(COLOR_RESET)\n"
	@mkdir -p $(LIMINE_BINARY_DIR)
	@curl -sSL https://github.com/Limine-Bootloader/Limine/releases/download/v12.5.2/limine-binary.tar.gz | \
	tar -xzf - --strip-components=1 -C $(LIMINE_BINARY_DIR)
	@make -C $(LIMINE_BINARY_DIR) >/dev/null 2>&1
	@printf "\r\033[K$(COLOR_GREEN)[CHECK] Limine is downloaded [OK]$(COLOR_RESET)\n"