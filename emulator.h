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
#define DONE 0x3000

// *********** USED IN DECODER ************

#define MSB3(x) (((x) >> 13) & 0x07)
#define BL_OFF(x) ((x) & 0x1FFF)  // BL
#define DEST(x) ((x) & 0x07)  // D D D bits 0 to 2

#define MASK001X(x) (((x) >> 12) & 1)

// for MOVx intructions
#define MASK011(x)  (((x) >> 12) & 0x03)    // instruction
#define BYTE011(x) (((x) >> 3) & 0xFF)  // Data byte
// dabit shift 3 to right to get DRA D D D, giving 16 possibilities for the 16 total cpu registers
#define DABIT(x) ((((x) >> 11) & 1) << 3)  // data (0) or Addr (1) register


#define MASK1111(x)  (((x) >> 8) & 0x0F)  // instruction

enum OPCODE00100X {BR, CEX};
enum OPCODE10XX {MOVL, MOVLZ, MOVLS, MOVH};
enum OPCODE0011 {SRAorRRC, ADD, ADDC, SUB, SUBC, CMP, XOR, AND, OR, BIT, BIS, BIC, MOV, MOV_SRA, SWAP, SWAP_SRA};

extern int decode(unsigned short adr, unsigned short IR);
extern void decode_LD_ST(int inst);
extern void decode_LDR_STR(int inst);
extern void decode_BR_to_CLRCC(int inst);
extern void decode_SRA_to_SWAP(int inst);
// ****************************************

enum ACTION { read, write };
enum SIZE { byte, word };
/*
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

extern void update_psw(unsigned short src, unsigned short dst, unsigned short res, unsigned short wb);

psw PSW;
*/


extern void bus(unsigned short mar, unsigned short *mbr, enum ACTION rw, enum SIZE bw);
extern int loader();
extern void memory_dump();  // show contents of memory
extern int fetch();

#endif //XMX_EMULATOR_EMULATOR_H
