#ifndef SHELL_H
#define SHELL_H

#include <stdint.h>
#include <stdbool.h>
#include "console.h"
#include "video.h"

void get_command_shell(const char* command);

void get_command_shell(const char* command)
{
    Console_WriteLine(command);
    if(command[0] == 'c')
    {
        if(command[1] == 'l');
            if(command[2] == 'e');
                if(command[3] == 'a');
                    if(command[4] == 'r');
                        clear_screen();
    }
}
// Burası daha tamamlanmadı şuan için tamamen boş
#endif