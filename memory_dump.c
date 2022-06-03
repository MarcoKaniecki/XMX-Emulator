//
// Created by Marco Kaniecki on 2022-06-03.
//
#include "emulator.h"

// print out anything in memory that's not zero
void memory_dump()
{
    printf("\n******** DUMPING  MEMORY ********\n");

    for(unsigned int i = 0; i < sizeof(memory.byte); i++)
    {
        if (memory.byte[i] == 0)  // ignore anything in mem with a zero
            continue;
        printf("%X %X\n", i, memory.byte[i]);
    }
    printf("********* MEMORY DUMPED *********\n\n");
}
