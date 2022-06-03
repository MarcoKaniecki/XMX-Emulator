#include "emulator.h"

unsigned short regfile[2][16] = {0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0,
                                 0, 1, 2, 4, 6, 16, 32, -1};


// CPU FETCH, DECODE, EXECUTE
int main()
{
    // IR = instruction register
    unsigned short IR = 0;

    loader();

    memory_dump();
    // printf("STARTING ADDR: %X\n", regfile[0][PC]);

    // TODO: check DONE in decoder
    while (IR != 0x3000)
    {
        IR = fetch();
        if (IR != 0)
            printf("Sending to Decoder... %X\n", IR);

    }


    return 0;
}
