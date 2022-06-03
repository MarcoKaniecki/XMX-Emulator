#include <stdio.h>

#define BIT7(x) (((x) >> 7) & 1)
#define BIT15(x) (((x) >> 15) & 1)

enum ACTION { read, write };
enum SIZE { byte, word };

typedef struct psw
{
    unsigned short V:1;
    unsigned short N:1;
    unsigned short Z:1;
    unsigned short C:1;

} psw;

union MEMORY
{
    unsigned char byte[0x10000];
    unsigned short word[0x8000];
};

union word_byte
{
    unsigned char byte[2];
    unsigned short word;
};

union word_byte srcnum, dstnum;
union MEMORY memory = {0};

unsigned short regfile[2][16] = {0,0,0,0,0,0,0,0,0,
                                 0,0,0,0,0,0,0,
                                 0,1,2,4,6,16,32,-1};

unsigned carry[2][2][2] = {0,0,1,0,1,0,1,1};
unsigned overflow[2][2][2] = {0,1,0,0,0,0,1,0};

void bus(unsigned short mar, unsigned short *mbr, enum ACTION rw, enum SIZE bw);
void update_psw(unsigned short src, unsigned short dst, unsigned short res, unsigned short wb);

void memory_dump();  // show contents of memory

psw PSW;

int main()
{
    //**********************************************************
    // testing accessing memory
    unsigned short mar, mbr;

    memory.byte[0x2F00] = 0x44;
    memory.word[0x2000] = 0x5555;
    memory.word[0] = 0xFFFF;

    mar = 0;
    bus(mar, &mbr, 0, 1);
    printf("read: %X\n", mbr);

    mbr = 5;
    mar = 1000;
    bus(mar, &mbr, 1, 0);
    printf("write: %X\n", memory.byte[1000]);
    //**********************************************************
    // testing register file
    // reading from
    unsigned short RC, SRC;
    RC = 1;
    SRC = 6;
    srcnum.byte[0] = regfile[RC][SRC];
    printf("regfile byte: %d\n", srcnum.byte[0]);

    // writing to
    RC = 0;
    SRC = 1;
    dstnum.word = 0xFF23;
    regfile[RC][SRC] = dstnum.word;
    printf("regfile word: %X\n", regfile[RC][SRC]);
    //**********************************************************
    // testing psw
    update_psw(0xF000,0xF000,0,0);
    update_psw(0x55, 0x22, 0x33,1);
    update_psw(0,0,0,1);
    update_psw(0xF000, 0x1000, 0xE000, 0);
    //**********************************************************
    return 0;
}


void bus(unsigned short mar, unsigned short *mbr, enum ACTION rw, enum SIZE bw)
{
    /*
    * Bus (and memory access) emulator
    * - mar - memory address - refers to a byte location ( word is mar >> 1)
    * - mbr - pointer to data to read/write
    * - rw - READ|WRITE
    * - bw - BYTE|WORD
    */

    // word can only be written to even byte addr
    // to prevent that, mar gets shifted by 1 preventing a possible 1
    // in LSBit from changing the addr to being odd

    if (rw == read && bw == byte)  // read byte
    {
        *mbr = memory.byte[mar];
    }
    else if (rw == read && bw == word)  // read word
    {
        *mbr = memory.word[mar >> 1];
    }
    else if (rw == write && bw == byte)  // write byte
    {
        memory.byte[mar] = *mbr;
    }
    else  // write word
        memory.word[mar >> 1] = *mbr;
}


// print out anything in memory that's not zero
void memory_dump()
{
    for(int i = 0; i < sizeof(memory); i++)
    {
        if (memory.word[i] == 0)  // ignore anything in mem with a zero
            continue;
        printf("%X %X\n", i, memory.word[i]);
        i++;
    }
}


/*
 * Update the PSW bits (V, N, Z, C)
 * - using src, dst, and res values and whether word or byte
 * - ADD, ADDC, SUB, and SUBC
 */
void update_psw(unsigned short src, unsigned short dst, unsigned short res, unsigned short wb)
{
    unsigned short msbsrc, msbdst, msbres;  // most significant bits for src, dst, and res

    if (wb == 0)  // word
    {
        msbsrc = BIT15(src);
        msbdst = BIT15(dst);
        msbres = BIT15(res);
    }
    else  // byte
    {
        msbsrc = BIT7(src);
        msbdst = BIT7(dst);
        msbres = BIT7(res);
        res = res & 0xFF;  // mask high byte
    }

    // carry
    PSW.C = carry[msbsrc][msbdst][msbres];
    // overflow
    PSW.V = overflow[msbsrc][msbdst][msbres];
    // Zero
    PSW.Z = (res == 0);
    // Negative
    PSW.N = (msbres == 1);

    printf("Updated PSW - C:%d V:%d Z:%d N:%d\n", PSW.C, PSW.V, PSW.Z, PSW.N);
}