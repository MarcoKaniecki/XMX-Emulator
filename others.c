#include "emulator.h"

// sets breakpoint after instruction at highest memory location
void set_default_breakpoint(unsigned short adr)
{
    memory.word[(adr >> 1) + 1] = BREAK_INSTRUCTION;
}

// print out anything in memory that's not zero
void memory_dump()
{
    printf("\n******** DUMPING  MEMORY ********\n");
    unsigned int i = 0;
    while(memory.word[i] != BREAK_INSTRUCTION)
    {
        // only print when register isn't empty
        if (memory.word[i] != 0)
            printf("0x%04X %04X\n", i, memory.word[i]);
        i++;
    }
    printf("********* MEMORY DUMPED *********\n\n");
}


// ********* Code below provided by Dr. Hughes ****************
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