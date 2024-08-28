#ifndef VIDEO_H
#define VIDEO_H

#include <stdint.h>
#include "io.h"

void write_string_to_video_memory(const char* str);
void clear_screen();
void set_cursor_position(int x, int y);
void write_char_to_video_memory(char c);
void delete_char_from_video_memory(void);
void set_color(uint8_t color);
void scroll_screen();

char* video_memory = (char*)0xb8000;
int cursor_x = 0;
int cursor_y = 0;

uint8_t console_color = 0x00;

void set_color(uint8_t color) {
    console_color = color;
}

void write_string_to_video_memory(const char* str) {
    while (*str) {
        write_char_to_video_memory(*str);
        str++;
    }
}

void write_char_to_video_memory(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } 
    else {
        video_memory[(cursor_y * 80 + cursor_x) * 2] = c;
        video_memory[(cursor_y * 80 + cursor_x) * 2 + 1] = console_color;
        cursor_x++;
        if (cursor_x >= 80) {
            cursor_x = 0;
            cursor_y++;
        }
    }

    if (cursor_y >= 25) {
        scroll_screen();
        cursor_y = 24;
    }

    set_cursor_position(cursor_x, cursor_y);
}

void delete_char_from_video_memory(void) {
    if (cursor_x > 0) {
        cursor_x--;
    } else if (cursor_y > 0) {
        cursor_y--;
        cursor_x = 79;
    }

    video_memory[(cursor_y * 80 + cursor_x) * 2] = ' ';
    video_memory[(cursor_y * 80 + cursor_x) * 2 + 1] = console_color;

    set_cursor_position(cursor_x, cursor_y);
}

void clear_screen() {
    uint16_t* video_memory_ptr = (uint16_t*)0xb8000;
    uint16_t blank = (console_color << 8) | 0x20;

    for (int i = 0; i < 80 * 25; i++) {
        video_memory_ptr[i] = blank;
    }

    cursor_x = 0;
    cursor_y = 0;
    set_cursor_position(cursor_x, cursor_y);
    video_memory = (char*)0xb8000;
}

void set_cursor_position(int x, int y) {
    uint16_t position = y * 80 + x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((position >> 8) & 0xFF));
}

void scroll_screen() {
    uint16_t* video_memory_ptr = (uint16_t*)0xb8000;
    uint16_t blank = (console_color << 8) | 0x20;

    for (int i = 0; i < (25 - 1) * 80; i++) {
        video_memory_ptr[i] = video_memory_ptr[i + 80];
    }

    for (int i = (25 - 1) * 80; i < 25 * 80; i++) {
        video_memory_ptr[i] = blank;
    }
}

#endif // VIDEO_H
