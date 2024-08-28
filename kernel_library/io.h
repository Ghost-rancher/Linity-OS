#ifndef IO_H
#define IO_H

#include <stdint.h>

static inline void outb(uint16_t port, uint8_t val);
static inline uint8_t inb(uint16_t port);
void io_wait(void);

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

void io_wait(void) {
    asm volatile ("outb %%al, $0x80" : : "a"(0));
}

#endif // IO_H
