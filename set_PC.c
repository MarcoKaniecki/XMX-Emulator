//
// Created by Marco Kaniecki on 2022-06-04.
//
#include "emulator.h"

void set_PC(unsigned short adr)
{
    // TODO: specify addr should be word
    PC = adr;
    printf("Set PC to %X\n", PC);

    // prevent loader from overwriting custom PC location
    custom_PC = SET;
}