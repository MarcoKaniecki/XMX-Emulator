// sign extension, memdump, display register file and set initial cpu states
#include "emulator.h"

union word_byte regfile[2][16] = {0, 0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0,
                                  0, 1, 2, 4, 6, 16, 32, -1};


// ********* 2 functions below provided by Dr. Hughes ****************
/*
 - Extract and sign extend any bit for any 16-bit bit pattern
 - ECED 3403
 - 1 Jun 22
 *** Caveat Emptor - Buyer Beware ***
 *** Don't use this on faith - are you sure it works? ***
*/
#define NEGSIGN(x)	(0xFFFF << (x))

unsigned short sign_ext(unsigned short offset, unsigned short signbit)
{
    /* Sign extend at signbit
    - return sign-extended value
    */
    if (offset & (1 << signbit))
        offset |= NEGSIGN(signbit); /* bit set - negative */
    /* bit clear - positive */
    return offset;
}

unsigned short extract_bits(unsigned short value, unsigned short signbit)
{
    /*
    - Ignore bits to left of sign bit (that is, signbit + 1)
    - Should be a macro (probably optimized to one - why?)
    */

    return value & ~(NEGSIGN(signbit + 1));

}
// **************************************************************

// print out anything in memory from a given starting adr to end adr
void memory_dump(unsigned int start_adr, unsigned int end_adr)
{
    unsigned int curr_adr = start_adr;
    // Print contents of starting adr up to but not including ending adr
    // Prints number of MEM_DUMP_SEGMENT_SIZE bytes in 1 row then increments cur adr by that amount to print next segment
    while (curr_adr <= end_adr)
    {
        printf("0x%04X  ", curr_adr);
        for (int i = 0; i < MEM_DUMP_SEGMENT_SIZE; i++)
            printf("%02X ", memory.byte[curr_adr + i]);
        curr_adr = curr_adr + MEM_DUMP_SEGMENT_SIZE;
        printf("\n");
    }
}

// Print contents of register file, apart from constants
void display_regfile()
{
    printf("R0: %04X   A0: %04X\n", regfile[0][0].word, regfile[0][8].word);
    printf("R1: %04X   A1: %04X\n", regfile[0][1].word, regfile[0][9].word);
    printf("R2: %04X   A2: %04X\n", regfile[0][2].word, regfile[0][10].word);
    printf("R3: %04X   A3: %04X\n", regfile[0][3].word, regfile[0][11].word);
    printf("R4: %04X   BP: %04X\n", regfile[0][4].word, BP);  // regfile[0][12].word
    printf("R5: %04X   LR: %04X\n", regfile[0][5].word, LR);  // regfile[0][13].word
    printf("R6: %04X   SP: %04X\n", regfile[0][6].word, SP);  // regfile[0][14].word
    printf("R7: %04X   PC: %04X\n", regfile[0][7].word, PC);  // regfile[0][15].word
}

// when program starts initial values for PC, SP and PSW are set
void initial_CPU_state()
{
    PC = PC_default;
    SP = SP_default;
    PSW.C = CLEAR;
    PSW.N = CLEAR;
    PSW.V = CLEAR;
    PSW.Z = CLEAR;
}
