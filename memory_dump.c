//
// Created by Marco Kaniecki on 2022-06-03.
//
#include "emulator.h"

// print out anything in memory that's not zero
void memory_dump()
{
    printf("\n******** DUMPING  MEMORY ********\n");
    printf("W = [ B.1001 | B.1000 ]\n");

    for(unsigned int i = 0; i < sizeof(memory.byte); i++)
    {
        if (memory.byte[i] == 0)  // ignore anything in mem with a zero
            continue;
        // print same word index as previous, on odd numbers
        printf("W:%04X  B:%04X   %02X\n", (i % 2 == 0)? i/2 : (i - 1)/2, i, memory.byte[i]);
    }
    printf("********* MEMORY DUMPED *********\n\n");
}
