#ifndef UTILS_H
#define UTILS_H

#include "console.h"

int Length(const char* g);
char NumberToChar(int deger);
char* int_to_string(uint32_t value);
char* hex_to_string(uint32_t value);
void print_registers(void);
void print_all_registers(void);

int Length(const char* g) {
    int gh = 0;
    while (g[gh] != '\0') {
        gh++;
    }
    return gh;
}

char NumberToChar(int deger) {
    if(deger < 0 || deger > 9) {
        return 0;
    } else {
        char i = 48;
        int y = 0;
        while(i != 58) {
            if(deger == y) {
                return i;
            }
            y++;
            i++;
        }
        return 0;
    }
}

char* int_to_string(uint32_t value) {
    char temp[12];
    static char return_buffer[12];
    int i = 0;

    if (value == 0) {
        return_buffer[0] = '0';
        return_buffer[1] = '\0';
        return return_buffer;
    }

    while (value != 0) {
        temp[i++] = (value % 10) + '0';
        value /= 10;
    }

    temp[i] = '\0';

    int j = 0;
    for (--i; i >= 0; --i) {
        return_buffer[j++] = temp[i];
    }
    return_buffer[j] = '\0';
    return return_buffer;
}

const char hex_chars[] = "0123456789ABCDEF";

char* hex_to_string(uint32_t value) {
    static char return_buffer[16];
    return_buffer[0] = '0';
    return_buffer[1] = 'x';
    
    for (int i = 0; i < 8; i++) {
        return_buffer[9 - i] = hex_chars[value & 0xF];
        value >>= 4;
    }
    
    return_buffer[10] = '\0';
    return return_buffer;
}

void print_registers(void) {
    uint32_t eax, ebx, ecx, edx;
    uint32_t esi, edi, ebp, esp;
    uint32_t cr0, cr2, cr3, cr4;
    
    asm volatile (
        "mov %%eax, %0\n\t"
        "mov %%ebx, %1\n\t"
        "mov %%ecx, %2\n\t"
        "mov %%edx, %3\n\t"
        "mov %%esi, %4\n\t"
        "mov %%edi, %5\n\t"
        "mov %%ebp, %6\n\t"
        "mov %%esp, %7\n\t"
        : "=g" (eax), "=g" (ebx), "=g" (ecx), "=g" (edx), 
          "=g" (esi), "=g" (edi), "=g" (ebp), "=g" (esp)
    );

    asm volatile (
        "mov %%cr0, %0\n\t"
        "mov %%cr2, %1\n\t"
        "mov %%cr3, %2\n\t"
        "mov %%cr4, %3\n\t"
        : "=g" (cr0), "=g" (cr2), "=g" (cr3), "=g" (cr4)
    );
    
    Console_Write("EAX: ");
    Console_WriteLine(hex_to_string(eax));
    Console_Write("EBX: ");
    Console_WriteLine(hex_to_string(ebx));
    Console_Write("ECX: ");
    Console_WriteLine(hex_to_string(ecx));
    Console_Write("EDX: ");
    Console_WriteLine(hex_to_string(edx));
    Console_Write("ESI: ");
    Console_WriteLine(hex_to_string(esi));
    Console_Write("EDI: ");
    Console_WriteLine(hex_to_string(edi));
    Console_Write("EBP: ");
    Console_WriteLine(hex_to_string(ebp));
    Console_Write("ESP: ");
    Console_WriteLine(hex_to_string(esp));
    Console_Write("CR0: ");
    Console_WriteLine(hex_to_string(cr0));
    Console_Write("CR2: ");
    Console_WriteLine(hex_to_string(cr2));
    Console_Write("CR3: ");
    Console_WriteLine(hex_to_string(cr3));
    Console_Write("CR4: ");
    Console_WriteLine(hex_to_string(cr4));
}

void print_all_registers(void) {
    uint32_t eax, ebx, ecx, edx;
    uint32_t esi, edi, ebp, esp;
    uint32_t cr0, cr2, cr3, cr4;
    uint32_t cs, ds, ss, es, fs, gs;
    uint32_t eflags;

    asm volatile (
        "mov %%eax, %0\n\t"
        "mov %%ebx, %1\n\t"
        "mov %%ecx, %2\n\t"
        "mov %%edx, %3\n\t"
        "mov %%esi, %4\n\t"
        "mov %%edi, %5\n\t"
        "mov %%ebp, %6\n\t"
        "mov %%esp, %7\n\t"
        : "=g" (eax), "=g" (ebx), "=g" (ecx), "=g" (edx), 
          "=g" (esi), "=g" (edi), "=g" (ebp), "=g" (esp)
    );

    asm volatile (
        "mov %%cr0, %0\n\t"
        "mov %%cr2, %1\n\t"
        "mov %%cr3, %2\n\t"
        "mov %%cr4, %3\n\t"
        : "=g" (cr0), "=g" (cr2), "=g" (cr3), "=g" (cr4)
    );

    asm volatile (
        "mov %%cs, %0\n\t"
        "mov %%ds, %1\n\t"
        "mov %%ss, %2\n\t"
        "mov %%es, %3\n\t"
        "mov %%fs, %4\n\t"
        "mov %%gs, %5\n\t"
        : "=g" (cs), "=g" (ds), "=g" (ss), "=g" (es), "=g" (fs), "=g" (gs)
    );

    asm volatile (
        "pushf\n\t"
        "pop %0\n\t"
        : "=g" (eflags)
    );

    Console_Write("EAX: ");
    Console_WriteLine(hex_to_string(eax));
    Console_Write("EBX: ");
    Console_WriteLine(hex_to_string(ebx));
    Console_Write("ECX: ");
    Console_WriteLine(hex_to_string(ecx));
    Console_Write("EDX: ");
    Console_WriteLine(hex_to_string(edx));
    Console_Write("ESI: ");
    Console_WriteLine(hex_to_string(esi));
    Console_Write("EDI: ");
    Console_WriteLine(hex_to_string(edi));
    Console_Write("EBP: ");
    Console_WriteLine(hex_to_string(ebp));
    Console_Write("ESP: ");
    Console_WriteLine(hex_to_string(esp));
    Console_Write("CR0: ");
    Console_WriteLine(hex_to_string(cr0));
    Console_Write("CR2: ");
    Console_WriteLine(hex_to_string(cr2));
    Console_Write("CR3: ");
    Console_WriteLine(hex_to_string(cr3));
    Console_Write("CR4: ");
    Console_WriteLine(hex_to_string(cr4));
    Console_Write("CS: ");
    Console_WriteLine(hex_to_string(cs));
    Console_Write("DS: ");
    Console_WriteLine(hex_to_string(ds));
    Console_Write("SS: ");
    Console_WriteLine(hex_to_string(ss));
    Console_Write("ES: ");
    Console_WriteLine(hex_to_string(es));
    Console_Write("FS: ");
    Console_WriteLine(hex_to_string(fs));
    Console_Write("GS: ");
    Console_WriteLine(hex_to_string(gs));
    Console_Write("EFLAGS: ");
    Console_WriteLine(hex_to_string(eflags));
}



#endif // UTILS_H
