#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include "io.h"
#include "video.h"
#include "utils.h"

#define KBD_DATA_PORT 0x60
#define KBD_STATUS_PORT 0x64
#define LEFT_SHIFT_PRESSED 0x2A
#define LEFT_SHIFT_RELEASED 0xAA
#define RIGHT_SHIFT_PRESSED 0x36
#define RIGHT_SHIFT_RELEASED 0xB6

uint8_t pressed_keycode[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 
                             0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 
                             0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 
                             0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 
                             0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 
                             0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 
                             0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 
                             0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 
                             0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 
                             0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 
                             0x51, 0x52, 0x53};

uint8_t released_keycode[] = {0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 
                               0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 
                               0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 
                               0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 
                               0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 
                               0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 
                               0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 
                               0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xC0, 
                               0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 
                               0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 
                               0xD1, 0xD2, 0xD3};

static const char char_keycode[] = {
    0x1B,  // ESC
    '1',   // 1
    '2',   // 2
    '3',   // 3
    '4',   // 4
    '5',   // 5
    '6',   // 6
    '7',   // 7
    '8',   // 8
    '9',   // 9
    '0',   // 0
    '-',   // -
    '=',   // =
    0x08,  // Backspace
    0x09,  // Tab
    'q',   // q
    'w',   // w
    'e',   // e
    'r',   // r
    't',   // t
    'y',   // y
    'u',   // u
    'i',   // i
    'o',   // o
    'p',   // p
    '[',   // [
    ']',   // ]
    0x0D,  // Enter
    0x11,  // LCTRL
    'a',   // a
    's',   // s
    'd',   // d
    'f',   // f
    'g',   // g
    'h',   // h
    'j',   // j
    'k',   // k
    'l',   // l
    ';',   // ;
    '\'',  // '
    '`',   // `
    0x10,  // LShift
    '\\',  // '\'
    'z',   // z
    'x',   // x
    'c',   // c
    'v',   // v
    'b',   // b
    'n',   // n
    'm',   // m
    ',',   // ,
    '.',   // .
    '/',   // /
    0x10,  // RShift
    '*',   // Keypad *
    0x12,  // LAlt
    ' ',   // Space
    0x14,  // CapsLock
    0x3B,  // F1
    0x3C,  // F2
    0x3D,  // F3
    0x3E,  // F4
    0x3F,  // F5
    0x40,  // F6
    0x41,  // F7
    0x42,  // F8
    0x43,  // F9
    0x44,  // F10
    0x90,  // NumLock
    0x91,  // ScrollLock
    '7',   // Keypad 7
    '8',   // Keypad 8
    '9',   // Keypad 9
    '-',   // Keypad -
    '4',   // Keypad 4
    '5',   // Keypad 5
    '6',   // Keypad 6
    '+',   // Keypad +
    '1',   // Keypad 1
    '2',   // Keypad 2
    '3',   // Keypad 3
    '0',   // Keypad 0
    '.'    // Keypad .
};

uint8_t read_scancode(void);

uint8_t wait_for_keypress(void);

static uint8_t shift_pressed = 0;

static uint8_t lastkey = 0x00;

char return_key(uint8_t test);

uint8_t read_scancode(void) {
    while ((inb(KBD_STATUS_PORT) & 0x01) == 0) {

    }
    return inb(KBD_DATA_PORT);
}

char return_key(uint8_t test)
{
    for(int j = 0;j < 82;j++)
    {
        if(test == pressed_keycode[j])
        {
            return char_keycode[j];
        }
        /*else if(test == released_keycode[j])
        {
            return char_keycode[j];
        }*/
    }
    return 0x00;
}

uint8_t wait_for_keypress(void) {
    uint8_t scancode;
    while (1) {
        scancode = read_scancode();
        if (lastkey != scancode)
        {
            lastkey = scancode;
            return scancode;
        }
    }
    return scancode;
}
#endif // KEYBOARD_H
