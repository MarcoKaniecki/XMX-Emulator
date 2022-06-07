//
// Created by Marco Kaniecki on 2022-06-03.
//
#include "emulator.h"

// return instr/data from Effective address
int fetch()
{
    unsigned short mbr;

    CPU_CLOCK++;

    bus(PC, &mbr, read, word);
    printf("Fetching... 0x%04X %04X\n", PC, mbr);
    PC = PC + 2;  // Increment PC

    return mbr;
}