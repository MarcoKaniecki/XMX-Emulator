//
// Created by Marco Kaniecki on 2022-06-03.
//
#include "emulator.h"

void bus(unsigned short mar, unsigned short *mbr, enum ACTION rw, enum SIZE bw)
{
    /*
    * Bus (and memory access) emulator
    * - mar - memory address - refers to a byte location ( word is mar >> 1)
    * - mbr - pointer to data to read/write
    * - rw - READ|WRITE
    * - bw - BYTE|WORD
    */

    // word can only be written to even byte addr
    // to prevent that, mar gets shifted by 1 preventing a possible 1
    // in LSBit from changing the addr to being odd

    if (rw == read && bw == byte)  // read byte
    {
        *mbr = memory.byte[mar];
    }
    else if (rw == read && bw == word)  // read word
    {
        *mbr = memory.word[mar >> 1];
    }
    else if (rw == write && bw == byte)  // write byte
    {
        memory.byte[mar] = *mbr;
    }
    else  // write word
        memory.word[mar >> 1] = *mbr;

    CPU_CLOCK = CPU_CLOCK + 3;
}
