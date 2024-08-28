#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdint.h>
#include <stdbool.h>
#include "io.h"
#include "keyboard.h"
#include "utils.h"
#include "video.h"

char* Console_ReadLine();

void Console_WriteLine(const char* string);

void Console_Write(const char* string);

bool backspace_pressed = false;

char* Console_ReadLine() {
    static char line[1024];
    int line_cx = 0;

    while (1) {
        uint8_t scancode = wait_for_keypress();
        char ascii_variable = return_key(scancode);

        if (scancode == 0x8E && backspace_pressed == false) { // Backspace
            if (line_cx > 0) {
                backspace_pressed = true;
                line_cx--;
                delete_char_from_video_memory();
            }
        }

        if (ascii_variable != 0x00 && ascii_variable != 0x0D && backspace_pressed == false) {
            if (line_cx < 1023) {
                if(ascii_variable != 0x08)
                {
                    line[line_cx] = ascii_variable;
                    write_char_to_video_memory(ascii_variable);
                    line_cx++;
                }
            }
        }
        backspace_pressed = false;

        if (ascii_variable == 0x0D) { // Enter tuşu
            char newline = '\n';
            write_char_to_video_memory(newline);
            line[line_cx] = '\0';
            return line;
        }
    }
}

void Console_WriteLine(const char* string)
{
    write_string_to_video_memory(string);
    char newline = '\n';
    write_char_to_video_memory(newline);
}

void Console_Write(const char* string)
{
    write_string_to_video_memory(string);
}

#endif