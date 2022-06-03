//
// Created by Marco Kaniecki on 2022-06-02.
//

#ifndef XMX_EMULATOR_EMULATOR_H
#define XMX_EMULATOR_EMULATOR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_REC_LEN 128
#define BIT7(x) (((x) >> 7) & 1)
#define BIT15(x) (((x) >> 15) & 1)
#define PC 15

/*
enum ACTION { read, write };
enum SIZE { byte, word };

typedef struct psw
{
    unsigned short V:1;
    unsigned short N:1;
    unsigned short Z:1;
    unsigned short C:1;

} psw;
*/

union mem
{
    unsigned char byte[0x10000];
    unsigned short word[0x8000];
} MEM;


union word_byte
{
    unsigned char byte[2];
    unsigned short word;
};

extern union word_byte srcnum, dstnum;

extern union mem memory;

extern unsigned short regfile[2][16];
/*


unsigned carry[2][2][2] = {0,0,1,0,1,0,1,1};
unsigned overflow[2][2][2] = {0,1,0,0,0,0,1,0};

extern void bus(unsigned short mar, unsigned short *mbr, enum ACTION rw, enum SIZE bw);
extern void update_psw(unsigned short src, unsigned short dst, unsigned short res, unsigned short wb);

psw PSW;
*/

extern int loader();
extern void memory_dump();  // show contents of memory




#endif //XMX_EMULATOR_EMULATOR_H
