//
// Created by Marco Kaniecki on 2022-06-04.
//
#include "emulator.h"

union word_byte regfile[2][16] = {0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0,
                                              0, 1, 2, 4, 6, 16, 32, -1};


// Print contents of register file, apart from constants
void display_regfile()
{
    printf("R0: %04X   A0: %04X\n", regfile[0][0].word, regfile[0][8].word);
    printf("R1: %04X   A1: %04X\n", regfile[0][1].word, regfile[0][9].word);
    printf("R2: %04X   A2: %04X\n", regfile[0][2].word, regfile[0][10].word);
    printf("R3: %04X   A3: %04X\n", regfile[0][3].word, regfile[0][11].word);
    printf("R4: %04X   BP: %04X\n", regfile[0][4].word, regfile[0][12].word);
    printf("R5: %04X   LR: %04X\n", regfile[0][5].word, LR);  // regfile[0][13]
    printf("R6: %04X   SP: %04X\n", regfile[0][6].word, SP);  // regfile[0][14]
    printf("R7: %04X   PC: %04X\n", regfile[0][7].word, PC);  // regfile[0][15]
}
