//
// Created by Marco Kaniecki on 2022-06-03.
//
#include "emulator.h"

// print out anything in memory that's not zero
void memory_dump()
{
    printf("\n******** DUMPING  MEMORY ********\n");
    unsigned int i = 0;
    while(memory.word[i] != BREAK_INSTRUCTION)
    {
        // only print when register isn't empty
        if (memory.word[i] != 0)
            printf("0x%04X %04X\n", i, memory.word[i]);
        i++;
    }
    printf("********* MEMORY DUMPED *********\n\n");
}
