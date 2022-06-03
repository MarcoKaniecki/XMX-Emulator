#include <stdio.h>


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

void decode_LD_ST(int inst);
void decode_LDR_STR(int inst);
void decode_BR_to_CLRCC(int inst);
void decode_SRA_to_SWAP(int inst);

enum OPCODE00100X {BR, CEX};
enum OPCODE10XX {MOVL, MOVLZ, MOVLS, MOVH};
enum OPCODE0011 {SRAorRRC, ADD, ADDC, SUB, SUBC, CMP, XOR, AND, OR, BIT, BIS, BIC, MOV, MOV_SRA, SWAP, SWAP_SRA};


FILE *infile;

int main() {
    int addr, inst;

    // assuming file exists and is readable
    infile = fopen("Strings.DAT", "r");

    while(fscanf(infile, "%4X %4X", &addr, &inst) > 0)
    {
        printf("%04X %04X    ", addr, inst);

        // determine subroutine from opcode
        // look at 3 most significant bits first
        switch (MSB3(inst))
        {
            case 0:  // BL
                printf("BL     OFF:  #%04X", BL_OFF(inst));
                break;

            case 1:  // BR ... SWAP
                if (MASK001X(inst))
                    decode_SRA_to_SWAP(inst);
                else
                    decode_BR_to_CLRCC(inst);
                break;

            case 2:  // LD or ST
                decode_LD_ST(inst);
                break;

            case 3:
                printf("Illegal instruction");
                break;

            case 4:  // MOVL, MOVLZ
            case 5:  // MOVLS, MOVH
                // looking at bits 12 and 13
                if (MASK011(inst) == MOVL)
                    printf("MOVL   ");
                else if (MASK011(inst) == MOVLZ)
                    printf("MOVLZ  ");
                else if (MASK011(inst) == MOVLS)
                    printf("MOVLS  ");
                else  // == 3 MOVH
                    printf("MOVH   ");

                // print data and register
                printf("Data: #%02X Register: %d", BYTE011(inst), DABIT(inst) + DEST(inst));
                break;

            case 6:  // LDR
            case 7:  // STR
                decode_LDR_STR(inst);
                break;
        }
        printf("\n");
    }
    return 0;
}

// any instruction between and including BR and CLRCC get further processed here
void decode_BR_to_CLRCC(int inst)
{

}


// any instruction between and including SRA and SWAP get further processed here
void decode_SRA_to_SWAP(int inst)
{
    int opcode_segment2 = (inst >> 8) & 0x0F;

    switch (opcode_segment2)
    {
        case SRAorRRC:
            break;

        case ADD:
            break;

        case ADDC:
            break;

        case SUB:
            break;

        case SUBC:
            break;

        case CMP:
            break;

        case XOR:
            break;

        case AND:
            break;

        case OR:
            break;

        case BIT:
            break;

        case BIS:
            break;

        case BIC:
            break;

        case MOV:
        case MOV_SRA:
            break;

        case SWAP:
        case SWAP_SRA:
            break;
    }
}

// instruction is either LD or ST
void decode_LD_ST(int inst)
{
    int LDorST = (inst >> 11) & 1; // 0 = LD, 1 = ST
    int DI = (inst >> 10) & 1;  // direct or indexed addressing
    int WorB = (inst >> 6) & 1;  // 0 = word, 1 = byte
    int SRCreg = (inst >> 3) & 0x07;
    int DSTreg = inst & 0x07;
    int SDRA = (inst >> 9) & 1;  // either SRA or DRA

    // bit 8: Pre- or Post- increment (0) or decrement (1)
    // bit 7: Increment (+) or decrement (-), stored as 0 or 1 respectively
    int addr_modifier = (inst >> 7) & 0x03;

    if (DI == 0)  // direct addressing
    {
        // in direct SDRA, PRPO and ID can be ignored
        printf("%s.%c  SRCreg: %d  DSTreg: %d", (LDorST == 0) ? "LD" : "ST", (WorB == 0) ? 'W' : 'B', SRCreg, DSTreg);
        return;
    }

    // indexed addressing
    if (SDRA == 0)  // LD
    {
        // SDRA is actually DRA
        DSTreg = DSTreg | (SDRA << 3);  // addr or data
        SRCreg = SRCreg | 0x08;  // forces register to be addr reg
        printf("LD.%c ", (WorB == 0) ? 'W' : 'B');

        // detailed table on addr modifiers in XMX Design Document p.19
        printf("SRCreg: ");
        switch (addr_modifier)
        {
            case 0:  // pre-increment
                printf("+%d ", SRCreg);
                break;
            case 1:  // pre-decrement
                printf("-%d ", SRCreg);
                break;
            case 2:  // post-increment
                printf("%d+ ", SRCreg);
                break;
            case 3:  // post-decrement
                printf("%d- ", SRCreg);
                break;
        }
        printf("DSTreg: %d", DSTreg);
    }
    else  // ST
    {
        // SDRA is actually SRA
        DSTreg = DSTreg | 0x08;  // forces register to be addr reg
        SRCreg = SRCreg | (SDRA << 3);  // addr or data
        printf("ST.%c SRCreg: %d  ", (WorB == 0) ? 'W' : 'B', SRCreg);

        printf("DSTreg: ");
        switch (addr_modifier)
        {
            case 0:  // pre-increment
                printf("+%d", DSTreg);
                break;
            case 1:  // pre-decrement
                printf("-%d", DSTreg);
                break;
            case 2:  // post-increment
                printf("%d+", DSTreg);
                break;
            case 3:  // post-decrement
                printf("%d-", DSTreg);
                break;
        }
    }
}


// instruction is either LDR or STR
void decode_LDR_STR(int inst)
{
    int OFF = (inst >> 7) & 0x1F;  // signed 5 bit offset
    unsigned int SDRA = (inst >> 12) & 1;  // either SRA or DRA
    unsigned int WorB = (inst >> 6) & 1;  // 0 = word, 1 = byte
    unsigned int SRCreg = (inst >> 3) & 0x07;
    unsigned int DSTreg = inst & 0x07;

    // check if MSB is a 1, if yes then change to negative number
    // 0x20 = 0x1F - 1 = 11111 - 1
    OFF = (((OFF >> 4) & 1) == 1) ? OFF - 0x20 : OFF;

    if (SDRA == 0)  // LDR
    {
        // SDRA is actually DRA
        DSTreg = DSTreg | (SDRA << 3);  // addr or data
        SRCreg = SRCreg | 0x08;  // forces register to be addr reg
        printf("LDR");
    }
    else  // STR
    {
        // SDRA is actually SRA
        DSTreg = DSTreg | 0x08;  // forces register to be addr reg
        SRCreg = SRCreg | (SDRA << 3);  // addr or data
        printf("STR");
    }
    printf(".%c  SRCreg: %d  DSTreg: %d  Off: %d", (WorB == 0) ? 'W' : 'B', SRCreg, DSTreg, OFF);
}