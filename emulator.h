//
// Created by Marco Kaniecki on 2022-06-02.
//
// emulator.h

#ifndef XMX_EMULATOR_EMULATOR_H
#define XMX_EMULATOR_EMULATOR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USER_INPUT_LEN 32
#define MAX_REC_LEN 128
#define BIT7(x) (((x) >> 7) & 1)
#define BIT15(x) (((x) >> 15) & 1)

#define BP regfile[0][12].word
#define LR regfile[0][13].word
#define SP regfile[0][14].word
#define PC regfile[0][15].word

#define SET         1
#define TRUE        1
#define ON_state    1
#define OFF_state   0
#define FALSE       0
#define CLEAR       0
#define NUL         0
#define LF          10
#define MEM_DUMP_SEGMENT_SIZE 16

// *********** Initial CPU state **********
#define PC_default 0  // on p.81 in XMX Design Document it says 0x800, however in A1 debugger notes it says 0
#define SP_default 0x0800

#define breakpoint_default 0xFFFF

// EXTR stands for extract
#define EXTR_BIT(instr, loc) (((instr) >> (loc)) & 1)  // Extract a bit at a given location
#define EXTR_RC(x) (((x) >> 7) & 1)
#define EXTR_WB(x) (((x) >> 6) & 1)
#define EXTR_SC(x) (((x) >> 3) & 0x07)
#define DEST(x) ((x) & 0x07)  // D D D bits 0 to 2
#define CEX_C(x) (((x) >> 6) & 0x0F)
#define CEX_T(x) (((x) >> 3) & 0x07)
#define CEX_F(x) ((x) & 0x07)
#define EXTR_DRA(instr, loc) (((instr) >> (loc)) & 1)
#define EXTR_SRA(instr, loc) (((instr) >> (loc)) & 1)
#define B(x) (((x) >> 3) & 0xFF)
#define EXTR_SRC(x) (((x) >> 3) & 0x07)
#define MSB3(x) (((x) >> 13) & 0x07)
#define BL_OFF(x) ((x) & 0x1FFF)  // BL
#define BR_OFF(x) ((x) & 0x3FF)
#define LDR_STR_OFF(x) (((x) >> 7) & 0x1F)
#define LD_ADR(x) (((x) >> 3) & 0x07)
#define ST_ADR(x) ((x) & 0x07)
#define MASK001X(x) (((x) >> 12) & 1)
#define MOVx(x)  (((x) >> 12) & 0x03)

extern short decode_LD_ST(unsigned short inst);
extern short decode_LDR_STR(unsigned short inst);
extern short decode_BR_to_CLRCC(unsigned short inst);
extern short decode_SRA_to_SWAP(unsigned short inst);
extern short decode_ADDX_SUBX_CMPX(unsigned short inst);
// ****************************************

enum ACTION { read, write };
enum SIZE { word, byte };
enum BITS { Bit0, Bit1, Bit2, Bit3, Bit4, Bit5, Bit6, Bit7, Bit8, Bit9, Bit10, Bit11, Bit12, Bit13, Bit14, Bit15 };
enum SRAorRRC { SRA, RRC };
enum LD_ST_ADDRESSING {direct, indexed};
enum OPCODE10XX {MOVL, MOVLZ, MOVLS, MOVH};
enum OPCODE0011 {SRAorRRC, ADD, ADDC, SUB, SUBC, CMP, XOR, AND, OR, BIT, BIS, BIC, MOV, MOV_SRA, SWAP, SWAP_SRA};
enum CEX_INSTR { EQ, NE, CS_HS, CC_LO, MI, PL, VS, VC, HI, LS, GE, LT, GT, LE, TR, FL };

typedef enum INSTRUCTIONS { BL_i, BR_i, CEX_i, SWPB_i, SXT_i, SRAorRRC_i, ADD_i, ADDC_i, ADDX_i, SUB_i, SUBC_i, SUBX_i,
                            CMP_i, CMPX_i, XOR_i, AND_i, OR_i, BIT_i, BIS_i, BIC_i, MOV_i, SWAP_i, LD_i, ST_i, MOVx_i,
                            LDR_i, STR_i, END_i } INSTRUCTIONS;

extern INSTRUCTIONS decode(unsigned short inst);

extern FILE *infile;
extern char srec[MAX_REC_LEN];

typedef struct psw
{
    unsigned short V:1;
    unsigned short N:1;
    unsigned short Z:1;
    unsigned short C:1;

} psw;

extern psw PSW;

typedef struct cex
{
    unsigned short state;
    unsigned short TorF;
    unsigned short T_count;
    unsigned short F_count;
}cex;

cex CEX;

union mem
{
    unsigned char byte[0x10000];
    unsigned short word[0x8000];
};

extern union mem memory;

union word_byte
{
    unsigned short word;
    unsigned char byte[2];
};

extern union word_byte srcnum, dstnum;
extern union word_byte regfile[2][16];

extern unsigned short breakpoint;
extern unsigned short custom_PC;

extern unsigned carry[2][2][2];
extern unsigned overflow[2][2][2];

extern unsigned long CPU_CLOCK;

extern void execute(INSTRUCTIONS inst, unsigned short full_inst);

extern void initial_CPU_state();  // when program starts initial values for PC, SP and PSW are set
extern void display_regfile();
extern int loader();  // loads S-Records into memory
extern unsigned short fetch();  // fetches data/instruction from memory
extern void memory_dump(unsigned int start_adr, unsigned int end_adr);  // show contents of memory
extern void bus(unsigned short mar, unsigned short *mbr, enum ACTION rw, enum SIZE bw);  // used to access main memory
extern void update_psw(unsigned short src, unsigned short dst, unsigned short res, unsigned short wb);
extern void update_psw_BIS_BIC(unsigned short res, unsigned short wb);

// execute functions
extern void BL_instr(unsigned short OFF);
extern void BR_instr(unsigned short OFF);
extern void SWPB_instr(unsigned short DST);
extern void SXT_instr(unsigned short DST);
extern void CEX_instr(unsigned short C, unsigned short T, unsigned short F);
extern void SRAorRRC_instr(enum SRAorRRC instr, enum SIZE bw, unsigned short DST);
extern void ADDtoOR_instr(unsigned short instr, unsigned short SRC, unsigned short DST, unsigned short carry, unsigned short RC, enum SIZE bw);
extern void SWAP_instr(unsigned short SRA, unsigned short DRA, unsigned short SRC, unsigned short DST);
extern void MOVx_instr(unsigned short instr, unsigned short DRA, unsigned short B, unsigned short DST);
extern void MOV_instr(unsigned short SRA, unsigned short DRA, enum SIZE bw, unsigned short SRC, unsigned short DST);
extern void BIx_instr(unsigned short instr, unsigned short RC, enum SIZE bw, unsigned short SC, unsigned short DST);
extern void LDR_STR_instr(unsigned short instr, unsigned short SDRA ,unsigned short OFF, enum SIZE bw, unsigned short SRC, unsigned short DST);
extern void LD_instr(unsigned short DI, unsigned short SDRA, unsigned short PRPO, unsigned short ID, enum SIZE bw, unsigned short ADR, unsigned short DST);
extern void ST_instr(unsigned short DI, unsigned short SDRA, unsigned short PRPO, unsigned short ID, enum SIZE bw, unsigned short SRC, unsigned short ADR);

// Functions provided by Dr. Hughes
extern unsigned short sign_ext(unsigned short offset, unsigned short signbit);
extern unsigned short extract_bits(unsigned short value, unsigned short signbit);

#endif //XMX_EMULATOR_EMULATOR_H
