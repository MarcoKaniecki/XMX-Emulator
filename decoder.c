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
            // if (BL_OFF(inst) == 0)
            //    break;
            BL_instr(BL_OFF(inst));
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
            MOVx_instr(MOVx(inst), EXTR_DRA(inst, Bit11), B(inst), DEST(inst));

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
    unsigned short Mask11_10 = (inst >> 10) & 0x03;
    unsigned short Mask3 = EXTR_BIT(inst, Bit3);

    switch (Mask11_10)
    {
        case 0:  // BR
            BR_instr(BR_OFF(inst));
            break;
        case 1:  // CEX
            // TODO: yet to implement
            printf("CEX\n");
            break;
        case 2:  // SWPB or SXT
            if (Mask3 == 0)  // SWPB
            {
                SWPB_instr(DEST(inst));
            }
            else  // SXT
            {
                SXT_instr(DEST(inst));
            }
            break;
        default:
            printf("invalid\n");
    }
}


// any instruction between and including SRA and SWAP get further processed here
void decode_SRA_to_SWAP(int inst)
{
    printf("Decoding SRA to SWAP\n");

    int opcode_segment2 = (inst >> 8) & 0x0F;

    switch (opcode_segment2)
    {
        case SRAorRRC:
            SRAorRRC_instr(EXTR_BIT(inst, Bit7), EXTR_WB(inst), DEST(inst));
            break;
        case ADD:
            ADDtoOR_instr(opcode_segment2, EXTR_SC(inst), DEST(inst), 0, EXTR_RC(inst), EXTR_WB(inst));
            break;
        case ADDC:
            ADDtoOR_instr(opcode_segment2, EXTR_SC(inst), DEST(inst), PSW.C, EXTR_RC(inst), EXTR_WB(inst));
            break;
        case SUB:
            ADDtoOR_instr(opcode_segment2, EXTR_SC(inst), DEST(inst), 1, EXTR_RC(inst), EXTR_WB(inst));
            break;
        case SUBC:
            ADDtoOR_instr(opcode_segment2, EXTR_SC(inst), DEST(inst), PSW.C, EXTR_RC(inst), EXTR_WB(inst));
            break;
        case CMP:
        case XOR:
        case AND:
        case OR:
            ADDtoOR_instr(opcode_segment2, EXTR_SC(inst), DEST(inst), 0, EXTR_RC(inst), EXTR_WB(inst));
            break;
        case BIT:
            BIx_instr(BIT, EXTR_RC(inst), EXTR_WB(inst), EXTR_SC(inst), DEST(inst));
            break;
        case BIS:
            BIx_instr(BIS, EXTR_RC(inst), EXTR_WB(inst), EXTR_SC(inst), DEST(inst));
            break;
        case BIC:
            BIx_instr(BIC, EXTR_RC(inst), EXTR_WB(inst), EXTR_SC(inst), DEST(inst));
            break;
        case MOV:
        case MOV_SRA: // TODO: continuous loop issue
            MOV_instr(EXTR_SRA(inst, Bit8), EXTR_DRA(inst, Bit7), EXTR_WB(inst), EXTR_SRC(inst), DEST(inst));
            break;
        case SWAP:
        case SWAP_SRA:
            SWAP_instr(EXTR_SRA(inst, Bit8), EXTR_DRA(inst, Bit7), EXTR_SRC(inst), DEST(inst));
            break;
    }
}


// instruction is either LD or ST
void decode_LD_ST(int inst)
{
    printf("Decoding LD_ST\n");

    unsigned short LDorST = (inst >> 11) & 1; // 0 = LD, 1 = ST
    unsigned short DI = (inst >> 10) & 1;  // direct or indexed addressing
    unsigned short WorB = (inst >> 6) & 1;  // 0 = word, 1 = byte
    unsigned short SRCreg = (inst >> 3) & 0x07;
    unsigned short DSTreg = inst & 0x07;
    unsigned short SDRA = (inst >> 9) & 1;  // either SRA or DRA
    unsigned short PRPO = (inst >> 8) & 1;  // Pre- or Post- increment (0) or decrement (1)
    unsigned short ID = (inst >> 7) & 1;  // Increment (+) or decrement (-), stored as 0 or 1 respectively


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

        LD_instr(DI, PRPO, ID, WorB, SRCreg, DSTreg);
    }
    else  // ST
    {
        // SDRA is actually SRA
        DSTreg = DSTreg | 0x08;  // forces register to be addr reg
        SRCreg = SRCreg | (SDRA << 3);  // addr or data
        printf("ST.%c SRCreg: %d  ", (WorB == 0) ? 'W' : 'B', SRCreg);

        ST_instr(DI, PRPO, ID, WorB, SRCreg, DSTreg);
    }
}


// instruction is either LDR or STR
void decode_LDR_STR(int inst)
{
    printf("Decoding LDR_STR\n");

    unsigned short OFF = (inst >> 7) & 0x1F;  // signed 5 bit offset
    unsigned short SDRA = (inst >> 12) & 1;  // either SRA or DRA


    if (SDRA == LDR)
    {
        // SDRA is actually DRA
        printf("LDR\n");
        LDR_STR_instr(LDR, SDRA, OFF, EXTR_WB(inst), EXTR_SRC(inst), DEST(inst));
    }
    else  // STR
    {
        // SDRA is actually SRA
        printf("ST\n");
        LDR_STR_instr(STR, SDRA, OFF, EXTR_WB(inst), EXTR_SRC(inst), DEST(inst));

    }
    // printf(".%c  SRCreg: %d  DSTreg: %d  Off: %d\n", (WorB == 0) ? 'W' : 'B', SRCreg, DSTreg, OFF);
}