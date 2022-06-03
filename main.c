#include "emulator.h"

unsigned short regfile[2][16] = {0,0,0,0,0,0,0,0,0,
                                 0,0,0,0,0,0,0,
                                 0,1,2,4,6,16,32,-1};


// CPU FETCH, DECODE, EXECUTE
int main() {
    loader();
    printf("LOADER DONE\n");

    memory_dump();
    printf("MEMORY DUMPED\n");

    printf("STARTING ADDR: %X", regfile[0][PC]);
    return 0;
}
