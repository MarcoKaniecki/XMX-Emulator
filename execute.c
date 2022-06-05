//
// Created by Marco Kaniecki on 2022-06-05.
//
#include "emulator.h"

void ADDtoOR_instr(unsigned short instr, unsigned short RC, enum SIZE bw, unsigned short SC, unsigned short Dst)
{
    unsigned short temp_reg;

    temp_reg = regfile[RC][SC];

    if (bw == word)
    {
        regfile[0][Dst] = regfile[0][Dst]; // <operation> Temp Reg
    }
    else
    {
        return; // TODO: add byte operation
    }
}