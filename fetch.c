//
// Created by Marco Kaniecki on 2022-06-03.
//
// fetch.c
#include "emulator.h"

// return instr/data from Effective address
unsigned short fetch()
{
    unsigned short mbr;

    CPU_CLOCK++;

    bus(PC, &mbr, read, word);
    PC = PC + 2;  // Increment PC

    return mbr;
}
