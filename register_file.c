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
    printf("R4: %04X   A4: %04X\n", regfile[0][4].word, regfile[0][12].word);
    printf("R5: %04X   A5: %04X\n", regfile[0][5].word, LR);  // regfile[0][13]
    printf("R6: %04X   A6: %04X\n", regfile[0][6].word, SP);  // regfile[0][14]
    printf("R7: %04X   A7: %04X\n", regfile[0][7].word, PC);  // regfile[0][15]
}


// change contents of register file, apart from constants
void modify_regfile()
{
    char reg_type;
    int reg_num, wb, value;
    union word_byte num;

    // TODO: change so not random values can be input

    printf("Specify Register (R/A), number (0...7) and to change by word (0) or by byte (1)\n");
    printf("Example: write R 6 1 to access R6 by byte\n");
    printf("> ");
    scanf("%c %d %d", &reg_type, &reg_num, &wb);
    printf("Value?\n");
    getchar();
    printf("> ");
    scanf("%X", &value);  // TODO: scan as decimal or hex?
    getchar();

    // offset by 8 for addressing registers
    reg_num = (reg_type == 'A')? reg_num + 8: reg_num;

    if (wb == 0)  // word
    {
        num.word = value;
        regfile[0][reg_num].word = num.word;

        // TODO: find nicer way to display reg_num?
        printf("Register %c%d set to 0x%X\n", reg_type, (reg_type == 'A')? reg_num - 8: reg_num, value);
    }
    else if (wb == 1)  // byte
    {
        printf("Yet to implement\n");  // TODO: modify by byte
    }
}