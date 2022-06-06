//
// Created by Marco Kaniecki on 2022-06-02.
//

#ifndef XMX_EMULATOR_EMULATOR_H
#define XMX_EMULATOR_EMULATOR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USER_INPUT_LEN 32
#define MAX_REC_LEN 128
#define BIT7(x) (((x) >> 7) & 1)
#define BIT15(x) (((x) >> 15) & 1)

#define LR regfile[0][13].word
#define SP regfile[0][14].word
#define PC regfile[0][15].word

#define SET 1
#define TRUE 1
#define FALSE 0
#define CLEAR 0
#define END 0

#define BREAK_INSTRUCTION 0x6000


extern unsigned long CPU_CLOCK;
// *********** Initial CPU state **********
#define PC_default 0x0800  // see p.81 in XMX Design Document
#define SP_default 0x0800


// *********** USED IN DECODER ************
#define EXTR_BIT(instr, loc) (((instr) >> (loc)) & 1)

#define RC(x) (((x) >> 7) & 1)  // TODO: add to something instr
#define WB(x) (((x) >> 6) & 1)
#define SC(x) (((x) >> 3) & 0x07)
#define DEST(x) ((x) & 0x07)  // D D D bits 0 to 2

#define DRA(instr, loc) (((instr) >> (loc)) & 1)
#define SRA(instr, loc) (((instr) >> (loc)) & 1)
#define B(x) (((x) >> 3) & 0xFF)
#define SRC(x) (((x) >> 3) & 0x07)



#define MSB3(x) (((x) >> 13) & 0x07)
#define BL_OFF(x) ((x) & 0x1FFF)  // BL


#define MASK001X(x) (((x) >> 12) & 1)

// for MOVx intructions
#define MOVx(x)  (((x) >> 12) & 0x03)    // instruction
#define BYTE011(x) (((x) >> 3) & 0xFF)  // Data byte
// dabit shift 3 to right to get DRA D D D, giving 16 possibilities for the 16 total cpu registers
#define DABIT(x) ((((x) >> 11) & 1) << 3)  // data (0) or Addr (1) register

#define MASK1111(x)  (((x) >> 8) & 0x0F)  // instruction

enum OPCODE00100X {BR, CEX};
enum OPCODE10XX {MOVL, MOVLZ, MOVLS, MOVH};
enum OPCODE0011 {SRAorRRC, ADD, ADDC, SUB, SUBC, CMP, XOR, AND, OR, BIT, BIS, BIC, MOV, MOV_SRA, SWAP, SWAP_SRA};

extern int decode(unsigned short IR);
extern void decode_LD_ST(int inst);
extern void decode_LDR_STR(int inst);
extern void decode_BR_to_CLRCC(int inst);
extern void decode_SRA_to_SWAP(int inst);
// ****************************************

enum ACTION { read, write };
enum SIZE { byte, word };
enum ADD_SUB { add, sub };
enum BITS { BIT0, BIT1, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7, BIT8, BIT9, BIT10, BIT11, BIT12, BIT13, BIT14, BIT15 };


typedef struct psw
{
    unsigned short V:1;
    unsigned short N:1;
    unsigned short Z:1;
    unsigned short C:1;

} psw;


union mem
{
    unsigned char byte[0x10000];
    unsigned short word[0x8000];
} MEM;


union word_byte
{
    unsigned short word;
    unsigned char byte[2];
};

extern union word_byte srcnum, dstnum;

extern union mem memory;

extern union word_byte regfile[2][16];

extern unsigned short custom_breakpoint_loc;  // contains address of where custom breakpoint is
extern unsigned short custom_PC;  // check in loader if custom PC has been set, set in set_starting_adr.c

// when a custom breakpoint is set an addr containing data/instr may be overwritten
extern unsigned short data_overwritten_at_breakpoint;


extern unsigned carry[2][2][2];
extern unsigned overflow[2][2][2];


extern psw PSW;


extern void set_default_breakpoint(unsigned short adr);
extern void set_custom_breakpoint(unsigned short adr);
extern void set_PC(unsigned short adr);
extern void display_regfile();
extern void modify_regfile();

extern void bus(unsigned short mar, unsigned short *mbr, enum ACTION rw, enum SIZE bw);
extern int loader();
extern void memory_dump();  // show contents of memory
extern int fetch();

extern void update_psw(unsigned short src, unsigned short dst, unsigned short res, unsigned short wb);


// execute functions
extern void SWPB_instr(unsigned short DST);
extern void ADDtoOR_instr(unsigned short instr, unsigned short SRC, unsigned short DST, unsigned short carry, unsigned short RC, enum SIZE bw);
extern void SWAP_instr(unsigned short SRA, unsigned short DRA, unsigned short SRC, unsigned short DST);
extern void MOVx_instr(unsigned short instr, unsigned short DRA, unsigned short B, unsigned short DST);
extern void MOV_instr(unsigned short SRA, unsigned short DRA, enum SIZE bw, unsigned short SRC, unsigned short DST);




// Functions provided by Dr. Hughes
unsigned short sign_ext(unsigned short offset, unsigned short signbit);
unsigned short extract_bits(unsigned short value, unsigned short signbit);

#endif //XMX_EMULATOR_EMULATOR_H
