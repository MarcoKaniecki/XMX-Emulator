//
// Created by Marco Kaniecki on 2022-06-03.
//
#include "emulator.h"

// return instr/data from Effective address
int fetch()
{
    unsigned short mar, mbr;

    mar = PC;
    bus(mar, &mbr, read, word);
    PC = PC + 2;  // Increment PC by 2 because of word
    if (mbr != 0)
        printf("Fetching... %04X %04X\n", mar, mbr);

    return mbr;
}