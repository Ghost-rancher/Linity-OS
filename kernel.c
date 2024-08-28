#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "kernel_library/video.h"
#include "kernel_library/utils.h"
#include "kernel_library/keyboard.h"
#include "kernel_library/console.h"
#include "kernel_library/shell.h"

void memset(void* ptr, int value, size_t num);

void kernel_loop();

void memset(void* ptr, int value, size_t num) {
    uint8_t* p = (uint8_t*) ptr;
    while (num--) {
        *p++ = (uint8_t) value;
    }
}

void kernel_main() {
    set_color(0x1F);
    clear_screen();
    
    Console_WriteLine("Kernel is Loaded");

    print_all_registers();

    kernel_loop();
}

void kernel_loop()
{
    Console_Write("Kernel>> ");
    char *command = Console_ReadLine();
    get_command_shell(command);
    kernel_loop();
}