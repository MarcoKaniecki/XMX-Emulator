#include "emulator.h"


INSTRUCTIONS decode(unsigned short inst)
{
    CPU_CLOCK++;

    printf("Decoding... %04X  case: %d -> ", inst, MSB3(inst));

    // look at 3 most significant bits first
    switch (MSB3(inst))
    {
        case 0:  // BL
            printf("BL\n");
            return BL_i;
            break;
        case 1:  // BR ... SWAP
            printf("BR to SWAP\n");
            if (MASK001X(inst))
                return decode_SRA_to_SWAP(inst);
            else
                return decode_BR_to_CLRCC(inst);
            break;
        case 2:  // LD or ST
            printf("LD or ST\n");
            return decode_LD_ST(inst);
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
            printf("MOVx\n");
            return MOVx_i;
            break;
        case 6:  // LDR
        case 7:  // STR
            printf("LDR or STR\n");
            return decode_LDR_STR(inst);
            break;
        default:
            printf("invalid\n");
    }
    return 1;
}


// any instruction between and including BR and CLRCC get further processed here
short decode_BR_to_CLRCC(unsigned short inst)
{
    unsigned short Mask11_10 = (inst >> 10) & 0x03;
    unsigned short Mask3 = EXTR_BIT(inst, Bit3);

    switch (Mask11_10)
    {
        case 0:  // BR
            return BR_i;
        case 1:  // CEX
            // TODO: yet to implement
            printf("CEX\n");
            break;
        case 2:  // SWPB or SXT
            if (Mask3 == 0)  // SWPB
                return SWPB_i;
            else  // SXT
                return SXT_i;
        default:
            printf("invalid\n");
    }
    return 0;
}

// any instruction between and including SRA and SWAP get further processed here
short decode_SRA_to_SWAP(unsigned short inst)
{
    int opcode_segment2 = (inst >> 8) & 0x0F;

    switch (opcode_segment2)
    {
        case SRAorRRC:
            return SRAorRRC_i;
        case ADD:
            return ADD_i;
        case ADDC:
            return ADDC_i;
        case SUB:
            return SUB_i;
        case SUBC:
            return SUBC_i;
        case CMP:
            return CMP_i;
        case XOR:
            return XOR_i;
        case AND:
            return AND_i;
        case OR:
            return OR_i;
        case BIT:
            return BIT_i;
        case BIS:
            return BIS_i;
        case BIC:
            return BIC_i;
        case MOV:
        case MOV_SRA:
            return MOV_i;
        case SWAP:
        case SWAP_SRA:
            return SWAP_i;
        default:
            printf("invalid\n");
    }
    return 0;
}

// instruction is either LD or ST
short decode_LD_ST(unsigned short inst)
{
    unsigned short LDorST = (inst >> 11) & 1;  // either SRA or DRA
    printf("LDorST = %d\n", LDorST);
    if (LDorST == 0)  // LD
    {
        return LD_i;
    }
    else  // ST
    {
        printf("returning ST num: %d\n", ST_i);
        return ST_i;
    }

}

// instruction is either LDR or STR
short decode_LDR_STR(unsigned short inst)
{
    unsigned short SDRA = (inst >> 12) & 1;  // either SRA or DRA

    if (SDRA == LDR)
        return LDR_i;  // SDRA is actually DRA
    else  // STR
        return STR_i;  // SDRA is actually SRA
}