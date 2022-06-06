#include "emulator.h"


int decode(unsigned short IR)
{
    unsigned short inst;

    inst = IR;

    CPU_CLOCK++;

    // printf("decoding... %04X %04X\n", addr, inst);

    // determine subroutine from opcode
    // look at 3 most significant bits first
    switch (MSB3(inst))
    {
        case 0:  // BL
            if (BL_OFF(inst) == 0)
                break;
            printf("BL     OFF:  #%04X\n", BL_OFF(inst));
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
            if (inst == BREAK_INSTRUCTION)
            {
                printf("END\n");
                return END;
            }
            printf("Illegal instruction\n");
            break;

        case 4:  // MOVL, MOVLZ
        case 5:  // MOVLS, MOVH
            MOVx_instr(MOVx(inst), DRA(inst, BIT11), B(inst), DEST(inst));

            // print data and register
            printf("Data: #%02X Register: %d\n", BYTE011(inst), DABIT(inst) + DEST(inst));
            break;

        case 6:  // LDR
        case 7:  // STR
            decode_LDR_STR(inst);
            break;
    }
    return 1;
}


// any instruction between and including BR and CLRCC get further processed here
void decode_BR_to_CLRCC(int inst)
{
    printf("Decoding BR to CLRCC\n");
    // TODO: finish this
    // SWPB_instr(DEST(inst));
}


// any instruction between and including SRA and SWAP get further processed here
void decode_SRA_to_SWAP(int inst)
{
    printf("Decoding SRA to SWAP\n");

    int opcode_segment2 = (inst >> 8) & 0x0F;

    switch (opcode_segment2)
    {
        case SRAorRRC:
            break;

        case ADD:
            ADDtoOR_instr(opcode_segment2, SC(inst), DEST(inst), 0, RC(inst), WB(inst));
            break;

        case ADDC:
            ADDtoOR_instr(opcode_segment2, SC(inst), DEST(inst), PSW.C, RC(inst), WB(inst));
            break;

        case SUB:
            ADDtoOR_instr(opcode_segment2, SC(inst), DEST(inst), 1, RC(inst), WB(inst));
            break;

        case SUBC:
            ADDtoOR_instr(opcode_segment2, SC(inst), DEST(inst), PSW.C, RC(inst), WB(inst));
            break;

        case CMP:
        case XOR:
        case AND:
        case OR:
            ADDtoOR_instr(opcode_segment2, SC(inst), DEST(inst), 0, RC(inst), WB(inst));
            break;

        case BIT:
            break;

        case BIS:
            break;

        case BIC:
            break;

        case MOV:
        case MOV_SRA:
            MOV_instr(SRA(inst, BIT8), DRA(inst, BIT7), WB(inst), SRC(inst), DEST(inst));
            break;

        case SWAP:
        case SWAP_SRA:
            SWAP_instr(SRA(inst, BIT8), DRA(inst, BIT7), SRC(inst), DEST(inst));
            break;
    }
}


// instruction is either LD or ST
void decode_LD_ST(int inst)
{
    printf("Decoding LD_ST\n");

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
        printf("%s.%c  SRCreg: %d  DSTreg: %d\n", (LDorST == 0) ? "LD" : "ST", (WorB == 0) ? 'W' : 'B', SRCreg, DSTreg);
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
        printf("DSTreg: %d\n", DSTreg);
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
        printf("\n");
    }
}


// instruction is either LDR or STR
void decode_LDR_STR(int inst)
{
    printf("Decoding LDR_STR\n");

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
    printf(".%c  SRCreg: %d  DSTreg: %d  Off: %d\n", (WorB == 0) ? 'W' : 'B', SRCreg, DSTreg, OFF);
}