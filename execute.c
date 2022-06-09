//
// Created by Marco Kaniecki on 2022-06-05.
//
#include "emulator.h"

union word_byte srcnum, dstnum;

void execute(INSTRUCTIONS inst, unsigned short full_inst)
{
    CPU_CLOCK++;

    switch (inst)
    {
        case BL_i:
            CEX.state = OFF_state;
            if (BL_OFF(full_inst) != 0)
                printf("BL OFF: %X\n", BL_OFF(full_inst));
            BL_instr(BL_OFF(full_inst));
            break;
        case BR_i:
            CEX.state = OFF_state;
            printf("BR OFF: %X\n", BR_OFF(full_inst));
            BR_instr(BR_OFF(full_inst));
            break;
        case CEX_i:
            printf("CEX\n");
            CEX_instr(CEX_C(full_inst), CEX_T(full_inst), CEX_F(full_inst));
            break;
        case SWPB_i:
            printf("SWPB\n");
            SWPB_instr(DEST(full_inst));
            break;
        case SXT_i:
            printf("SXT\n");
            SXT_instr(DEST(full_inst));
            break;
        case SRAorRRC_i:
            printf("SRA or RRC\n");
            SRAorRRC_instr(EXTR_BIT(full_inst, Bit7), EXTR_WB(full_inst), DEST(full_inst));
            break;
        case ADD_i:
            printf("ADD\n");
            ADDtoOR_instr(ADD, EXTR_SC(full_inst), DEST(full_inst), 0, EXTR_RC(full_inst), EXTR_WB(full_inst));
            break;
        case ADDC_i:
            printf("ADDC\n");
            ADDtoOR_instr(ADDC, EXTR_SC(full_inst), DEST(full_inst), PSW.C, EXTR_RC(full_inst), EXTR_WB(full_inst));
            break;
        case SUB_i:
            printf("SUB\n");
            ADDtoOR_instr(SUB, EXTR_SC(full_inst), DEST(full_inst), 1, EXTR_RC(full_inst), EXTR_WB(full_inst));
            break;
        case SUBC_i:
            printf("SUBC\n");
            ADDtoOR_instr(SUBC, EXTR_SC(full_inst), DEST(full_inst), PSW.C, EXTR_RC(full_inst), EXTR_WB(full_inst));
            break;
        case CMP_i:
            printf("CMP\n");
            ADDtoOR_instr(CMP, EXTR_SC(full_inst), DEST(full_inst), 0, EXTR_RC(full_inst), EXTR_WB(full_inst));
            break;
        case XOR_i:
            printf("XOR\n");
            ADDtoOR_instr(XOR, EXTR_SC(full_inst), DEST(full_inst), 0, EXTR_RC(full_inst), EXTR_WB(full_inst));
            break;
        case AND_i:
            printf("AND\n");
            ADDtoOR_instr(AND, EXTR_SC(full_inst), DEST(full_inst), 0, EXTR_RC(full_inst), EXTR_WB(full_inst));
            break;
        case OR_i:
            printf("OR\n");
            ADDtoOR_instr(OR, EXTR_SC(full_inst), DEST(full_inst), 0, EXTR_RC(full_inst), EXTR_WB(full_inst));
            break;
        case BIT_i:
            printf("BIT\n");
            BIx_instr(BIT, EXTR_RC(full_inst), EXTR_WB(full_inst), EXTR_SC(full_inst), DEST(full_inst));
            break;
        case BIS_i:
            printf("BIS\n");
            BIx_instr(BIS, EXTR_RC(inst), EXTR_WB(full_inst), EXTR_SC(full_inst), DEST(full_inst));
            break;
        case BIC_i:
            printf("BIC\n");
            BIx_instr(BIC, EXTR_RC(inst), EXTR_WB(full_inst), EXTR_SC(full_inst), DEST(full_inst));
            break;
        case MOV_i:
            printf("MOV\n");
            MOV_instr(EXTR_SRA(full_inst, Bit8), EXTR_DRA(full_inst, Bit7), EXTR_WB(full_inst), EXTR_SRC(full_inst), DEST(full_inst));
            break;
        case SWAP_i:
            printf("SWAP\n");
            SWAP_instr(EXTR_SRA(full_inst, Bit8), EXTR_DRA(full_inst, Bit7), EXTR_SRC(full_inst), DEST(full_inst));
            break;
        case LD_i:
            printf("LD\n");
            LD_instr(EXTR_BIT(full_inst, Bit10), EXTR_BIT(full_inst, Bit9), EXTR_BIT(full_inst, Bit8),
                     EXTR_BIT(full_inst, Bit7), EXTR_WB(full_inst), LD_ADR(full_inst), DEST(full_inst));
            break;
        case ST_i:
            printf("ST\n");
            ST_instr(EXTR_BIT(full_inst, Bit10), EXTR_BIT(full_inst, Bit9), EXTR_BIT(full_inst, Bit8),
                     EXTR_BIT(full_inst, Bit7), EXTR_WB(full_inst), EXTR_SC(full_inst), ST_ADR(full_inst));
            break;
        case MOVx_i:
            printf("MOVx instr: %X\n", full_inst);
            printf("MOVx instr num: %d\n", MOVx(full_inst));
            MOVx_instr(MOVx(full_inst), EXTR_DRA(full_inst, Bit11), B(full_inst), DEST(full_inst));
            break;
        case LDR_i:
            printf("LDR\n");
            LDR_STR_instr(0, EXTR_BIT(full_inst, Bit12), LDR_STR_OFF(full_inst), EXTR_WB(full_inst), EXTR_SRC(full_inst), DEST(full_inst));
            break;
        case STR_i:
            printf("STR\n");
            LDR_STR_instr(1, EXTR_BIT(full_inst, Bit12), LDR_STR_OFF(full_inst), EXTR_WB(full_inst), EXTR_SRC(full_inst), DEST(full_inst));
            break;
        default:
            printf("invalid\n");
    }
}

// conditional execution
void CEX_instr(unsigned short C, unsigned short T, unsigned short F)
{
    CEX.state = ON_state;
    CEX.T_count = T;
    CEX.F_count = F;
    
    switch(C)
    {
        case EQ:
            if(PSW.Z == SET)
                CEX.TorF = TRUE;
            else
                CEX.TorF = FALSE;
            break;
        case NE:
            if(PSW.Z == CLEAR)
                CEX.TorF = TRUE;
            else
                CEX.TorF = FALSE;
            break;
        case CS_HS:
            if(PSW.C == SET)
                CEX.TorF = TRUE;
            else
                CEX.TorF = FALSE;
            break;
        case CC_LO:
            if(PSW.C == CLEAR)
                CEX.TorF = TRUE;
            else
                CEX.TorF = FALSE;
            break;
        case MI:
            if(PSW.N == SET)
                CEX.TorF = TRUE;
            else
                CEX.TorF = FALSE;
            break;
        case PL:
            if(PSW.N == CLEAR)
                CEX.TorF = TRUE;
            else
                CEX.TorF = FALSE;
            break;
        case VS:
            if(PSW.V == SET)
                CEX.TorF = TRUE;
            else
                CEX.TorF = FALSE;
            break;
        case VC:
            if(PSW.V == CLEAR)
                CEX.TorF = TRUE;
            else
                CEX.TorF = FALSE;
            break;
        case HI:
            if(PSW.C == SET && PSW.Z == CLEAR)
                CEX.TorF = TRUE;
            else
                CEX.TorF = FALSE;
            break;
        case LS:
            if(PSW.C == CLEAR && PSW.Z == SET)
                CEX.TorF = TRUE;
            else
                CEX.TorF = FALSE;
            break;
        case GE:
            if(PSW.N == PSW.V)
                CEX.TorF = TRUE;
            else
                CEX.TorF = FALSE;
            break;
        case LT:
            if(PSW.N != PSW.V)
                CEX.TorF = TRUE;
            else
                CEX.TorF = FALSE;
            break;
        case GT:
            if((PSW.Z == CLEAR) && (PSW.N == PSW.V))
                CEX.TorF = TRUE;
            else
                CEX.TorF = FALSE;
            break;
        case LE:
            if((PSW.Z == SET) && (PSW.N != PSW.V))
                CEX.TorF = TRUE;
            else
                CEX.TorF = FALSE;
            break;
        case TR:
        case FL:
            printf("ignored\n");
            break;
        default:
            printf("invalid\n");
    }
}

// branch with link, return to LR loc after subroutine is done
void BL_instr(unsigned short OFF)
{
    LR = PC;
    PC = PC + (sign_ext(OFF,Bit12) << 1);
    printf("sign ext offset: %d, %x\n", sign_ext(OFF,Bit12) << 1, sign_ext(OFF,Bit12) << 1);
}

// unconditional branch
void BR_instr(unsigned short OFF)
{
    PC = PC + (sign_ext(OFF, Bit9) << 1);
}

// swap bytes in DST data register
void SWPB_instr(unsigned short DST)
{
    union word_byte temp;

    temp.byte[0] = regfile[0][DST].byte[0];
    regfile[0][DST].byte[0] = regfile[0][DST].byte[1];
    regfile[0][DST].byte[1] = temp.byte[0];
}

// performs all ADD to OR instructions
void ADDtoOR_instr(unsigned short instr, unsigned short SRC, unsigned short DST, unsigned short c, unsigned short RC, enum SIZE bw)
{
    union word_byte result;

    srcnum = regfile[RC][SRC];
    dstnum = regfile[0][DST];

    if (bw == word)
    {
        switch (instr)
        {
            case ADD:
            case ADDC:
                result.word = dstnum.word + srcnum.word + c;
                update_psw(srcnum.word, dstnum.word, result.word, word);
                break;
            case SUB:
            case SUBC:
                result.word = dstnum.word + ~srcnum.word + c;
                update_psw(~srcnum.word, dstnum.word, result.word, word);
                break;
            case CMP:
                result.word = dstnum.word + ~srcnum.word + 1;
                update_psw(~srcnum.word, dstnum.word, result.word, word);
                break;
            case XOR:
                result.word = dstnum.word ^ srcnum.word;
                update_psw(srcnum.word, dstnum.word, result.word, word);
                break;
            case AND:
                result.word = dstnum.word & srcnum.word;
                update_psw(srcnum.word, dstnum.word, result.word, word);
                break;
            case OR:
                result.word = dstnum.word | srcnum.word;
                update_psw(srcnum.word, dstnum.word, result.word, word);
                break;
            default:
                printf("invalid\n");
        }
        // all instr update the psw however only CMP does not overwrite the DST register
        if (instr != CMP)
            regfile[0][DST].word = result.word;
    }
    else  // byte
    {
        switch (instr)
        {
            case ADD:
            case ADDC:
                result.byte[0] = dstnum.byte[0] + srcnum.byte[0] + c;
                update_psw(srcnum.byte[0], dstnum.byte[0], result.byte[0], byte);
                break;
            case SUB:
            case SUBC:
                result.byte[0] = dstnum.byte[0] + ~srcnum.byte[0] + c;
                update_psw(~srcnum.byte[0], dstnum.byte[0], result.byte[0], byte);
                break;
            case CMP:
                result.byte[0] = dstnum.byte[0] + ~srcnum.byte[0] + 1;
                update_psw(~srcnum.byte[0], dstnum.byte[0], result.byte[0], byte);
                break;
            case XOR:
                result.byte[0] = dstnum.byte[0] ^ srcnum.byte[0];
                update_psw(srcnum.byte[0], dstnum.byte[0], result.byte[0], byte);
                break;
            case AND:
                result.byte[0] = dstnum.byte[0] & srcnum.byte[0];
                update_psw(srcnum.byte[0], dstnum.byte[0], result.byte[0], byte);
                break;
            case OR:
                result.byte[0] = dstnum.byte[0] | srcnum.byte[0];
                update_psw(srcnum.byte[0], dstnum.byte[0], result.byte[0], byte);
                break;
            default:
                printf("invalid\n");
        }
        if (instr != CMP){
            regfile[0][DST].byte[0] = result.byte[0];
        }
    }
}

// Exchange SRC register and DST register, can be either Data or Address registers
void SWAP_instr(unsigned short SRA, unsigned short DRA, unsigned short SRC, unsigned short DST)
{
    // [ DST/SRC | DRA/SRA << 3 ] gives a range of 0 to 15 for the registers
    union word_byte temp = regfile[0][DST | DRA << 3];

    regfile[0][DST | DRA << 3].word = regfile[0][SRC | SRA << 3].word;
    regfile[0][SRC | SRA << 3].word = temp.word;
}

// Move byte to DST (data or address) register
void MOVx_instr(unsigned short instr, unsigned short DRA, unsigned short B, unsigned short DST)
{
    unsigned short DST_reg = DST | (DRA << 3);
    printf("dst_reg = %d\n", DST_reg);

    switch (instr)
    {
        case MOVL:
            printf("movl\n");
            regfile[0][DST_reg].byte[0] = B;
            break;
        case MOVLZ:
            printf("movlz\n");
            regfile[0][DST_reg].byte[0] = B;
            regfile[0][DST_reg].byte[1] = 0;
            break;
        case MOVLS:
            printf("movls\n");
            regfile[0][DST_reg].byte[0] = B;
            regfile[0][DST_reg].byte[1] = 0xFF;
            break;
        case MOVH:
            printf("movh\n");
            regfile[0][DST_reg].byte[1] = B;
            break;
        default:
            printf("invalid instr\n");
    }
}

// Move SRC register to DST register, can be either DAta or Addressing registers
void MOV_instr(unsigned short SRA, unsigned short DRA, enum SIZE bw, unsigned short SRC, unsigned short DST)
{
    // [ DST/SRC | DRA/SRA << 3 ] gives a range of 0 to 15 for the registers
    unsigned short SRC_reg = SRC | (SRA << 3), DST_reg = DST | (DRA << 3);
    if (bw == word)
    {
        regfile[0][DST_reg].word = regfile[0][SRC_reg].word;
    }
    else
    {
        regfile[0][DST_reg].byte[0] = regfile[0][SRC_reg].byte[0];
    }
}

// Sign extend MSBit in LSByte of DST data register
void SXT_instr(unsigned short DST)
{
    regfile[0][DST].byte[0] = sign_ext(regfile[0][DST].byte[0], Bit7);
}

// SRA - shift DST data register right one bit arithmetic keeping sign
// RRC - rotate DST data register right by 1
// TODO: more comments
void SRAorRRC_instr(enum SRAorRRC instr, enum SIZE bw, unsigned short DST)
{
    union word_byte temp;

    if (instr == SRA)
    {
        printf("SRA\n");
        PSW.C = EXTR_BIT(regfile[0][DST].word, Bit0);
        if (bw == word)
        {
            temp.word = EXTR_BIT(regfile[0][DST].word, Bit15);
            regfile[0][DST].word = (regfile[0][DST].word >> 1) | (temp.word << 15);
        }
        else
        {
            temp.byte[0] = EXTR_BIT(regfile[0][DST].byte[0], Bit7);
            regfile[0][DST].byte[0] = (regfile[0][DST].byte[0] >> 1) | (temp.byte[0] << 7);
        }
    }
    else  // RRC
    {
        printf("RRC\n");
        temp.word = PSW.C;
        PSW.C = EXTR_BIT(regfile[0][DST].word, Bit0);
        if (bw == word)
        {
            regfile[0][DST].word = (regfile[0][DST].word >> 1) | (temp.word << 15);
        }
        else
        {
            regfile[0][DST].byte[0] = (regfile[0][DST].byte[0] >> 1) | (temp.byte[0] << 7);
        }
    }
}

// BIT - test any bit in a DST data register
// BIS - Set any bit in a DST data register
// BIC - Clear any bit in a DST data register
void BIx_instr(unsigned short instr, unsigned short RC, enum SIZE bw, unsigned short SC, unsigned short DST)
{
    union word_byte temp = regfile[RC][SC];
    switch (instr)
    {
        case BIT:
            // checks if DST bit is SET or not by shifting a 1 to the desired bit to check and ANDing it with the value to check
            if (bw == word)
                PSW.Z = ((regfile[0][DST].word & (1 << temp.word)) == 0);
            else
                PSW.Z = ((regfile[0][DST].byte[0] & (1 << temp.byte[0])) == 0);
            break;
        case BIS:
            // set a bit at location temp in DST register
            if (bw == word)
                regfile[0][DST].word |= 1 << temp.word;
            else  // set a bit at location temp in LSByte of DST register
                regfile[0][DST].byte[0] |= 1 << temp.byte[0];
            break;
        case BIC:
            // clear a bit at location temp in DST register
            if (bw == word)
                regfile[0][DST].word &= ~(1 << temp.word);
            else  // clear a bit at location temp in LSByte of DST register
                regfile[0][DST].byte[0] &= ~(1 << temp.byte[0]);
            break;
        default:
            printf("invalid\n");
    }
    // TODO: update PSW for BIS and BIC
    // update_psw();
}

// Load relative from SRC address register + offset to DST (data or address) register
// Store relative from SRC (data or address) register to DST address register + offset
void LDR_STR_instr(unsigned short instr, unsigned short SDRA ,unsigned short OFF, enum SIZE bw, unsigned short SRC, unsigned short DST)
{
    unsigned short EA, mbr;
    switch (instr)
    {
        case 0: // LDR
            printf("LDR \n");
            // Address reg is the SRC reg for LDR
            EA = (regfile[0][SRC | 0x08].word) + sign_ext(OFF, Bit4);
            printf("sign ext: %d\n", sign_ext(OFF, Bit4));
            if (bw == word)
            {
                printf("LDR word at addr: %X\n", EA);
                bus(EA, &mbr, read, word);
                printf("into reg: %d\n", (DST | (SDRA << 3)));
                regfile[0][DST | (SDRA << 3)].word = mbr;
            }
            else  // byte
            {
                bus(EA, &mbr, read, byte);
                regfile[0][DST | (SDRA << 3)].byte[0] = mbr;
            }
            break;
        case 1: // STR
            printf("STR\n");
            // Address reg is the DST reg for STR
            EA = (regfile[0][DST | 0x08].word) + sign_ext(OFF, Bit4);
            if (bw == word)
            {
                mbr = regfile[0][SRC | (SDRA << 3)].word;
                bus(EA, &mbr, write, word);
            }
            else  // byte
            {
                mbr = regfile[0][SRC | (SDRA << 3)].byte[0];
                bus(EA, &mbr, write, byte);
            }
            break;
        default:
            printf("invalid\n");
    }
}

// Load from SRC address register to DST (data or address) register
void LD_instr(unsigned short DI, unsigned short SDRA, unsigned short PRPO, unsigned short ID, enum SIZE bw, unsigned short ADR, unsigned short DST)
{
    unsigned short EA, mbr;

    DST = DST | (SDRA << 3);
    ADR = ADR | 0x08;

    // Effective address pre increment
    if (DI == direct)
    {
        EA = regfile[0][ADR].word;
    }
    else  // indexed
    {
        if (PRPO == 0)  // pre
        {
            if (ID == 0)  // increment
            {
                if (bw == word)
                    regfile[0][ADR].word = regfile[0][ADR].word + 2;
                else
                    regfile[0][ADR].byte[0] = regfile[0][ADR].byte[0] + 1;
            }
            else  // decrement
            {
                if (bw == word)
                    regfile[0][ADR].word = regfile[0][ADR].word - 2;
                else
                    regfile[0][ADR].byte[0] = regfile[0][ADR].byte[0] - 1;
            }
        }
        EA = regfile[0][ADR].word;
    }

    if (bw == word)
    {
        bus(EA, &mbr, read, word);
        regfile[0][DST].word = mbr;
    }
    else  // byte
    {
        bus(EA, &mbr, read, byte);
        regfile[0][DST].byte[0] = mbr;
    }

    if (DI == 1 && PRPO == 1)  // indexed post incr/decr
    {
        if (ID == 0)  // increment
        {
            if (bw == word)
                regfile[0][ADR].word = regfile[0][ADR].word + 2;
            else
                regfile[0][ADR].byte[0] = regfile[0][ADR].byte[0] + 1;
        }
        else  // decrement
        {
            if (bw == word)
                regfile[0][ADR].word = regfile[0][ADR].word - 2;
            else
                regfile[0][ADR].byte[0] = regfile[0][ADR].byte[0] - 1;
        }
    }
}

// Store from SRC (data or address) register to DST address register
void ST_instr(unsigned short DI, unsigned short SDRA, unsigned short PRPO, unsigned short ID, enum SIZE bw, unsigned short SRC, unsigned short ADR)
{
    unsigned short EA, mbr;

    ADR = ADR | 0x08;
    SRC = SRC | (SDRA << 3);

    // Effective address pre increment
    if (DI == direct)
    {
        EA = regfile[0][ADR].word;
    }
    else  // indexed
    {
        if (PRPO == 0)  // pre increment/decrement
        {
            if (ID == 0)  // increment
            {
                if (bw == word)
                    regfile[0][ADR].word = regfile[0][ADR].word + 2;
                else
                    regfile[0][ADR].byte[0] = regfile[0][ADR].byte[0] + 1;
            }
            else  // decrement
            {
                printf("got to pre decrement\n");
                if (bw == word)
                {
                    printf("got to pre decrement by word\n");
                    regfile[0][ADR].word = regfile[0][ADR].word - 2;
                }
                else
                    regfile[0][ADR].byte[0] = regfile[0][ADR].byte[0] - 1;
            }
        }
        EA = regfile[0][ADR].word;
    }

    if (bw == word)
    {
        mbr = regfile[0][SRC].word;
        bus(EA, &mbr, write, word);
    }
    else  // byte
    {
        mbr = regfile[0][SRC].byte[0];
        bus(EA, &mbr, write, byte);
    }

    if (DI == 1 && PRPO == 1)  // indexed post incr/decr
    {
        if (ID == 0)  // increment
        {
            if (bw == word)
                regfile[0][ADR].word = regfile[0][ADR].word + 2;
            else
                regfile[0][ADR].byte[0] = regfile[0][ADR].byte[0] + 1;
        }
        else  // decrement
        {
            if (bw == word)
                regfile[0][ADR].word = regfile[0][ADR].word - 2;
            else
                regfile[0][ADR].byte[0] = regfile[0][ADR].byte[0] - 1;
        }
    }
}
