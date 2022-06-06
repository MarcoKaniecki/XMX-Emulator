//
// Created by Marco Kaniecki on 2022-06-05.
//
#include "emulator.h"

union word_byte srcnum, dstnum;

// branch with link, return to LR loc after subroutine is done
void BL_instr(unsigned short OFF)
{
    LR = PC;
    PC = PC + (sign_ext(OFF,Bit12) << 1);
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
                break;
            case SUB:
            case SUBC:
                result.word = dstnum.word + ~srcnum.word + c;
                break;
            case CMP:
                result.word = dstnum.word + ~srcnum.word + 1;
                break;
            case XOR:
                result.word = dstnum.word ^ srcnum.word;
                break;
            case AND:
                result.word = dstnum.word & srcnum.word;
                break;
            case OR:
                result.word = dstnum.word | srcnum.word;
                break;
            default:
                printf("invalid\n");
        }
        // all instr update the psw however only CMP does not overwrite the DST register
        update_psw(srcnum.word, dstnum.word, result.word, word);
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
                break;
            case SUB:
            case SUBC:
                result.byte[0] = dstnum.byte[0] + ~srcnum.byte[0] + c;
                break;
            case CMP:
                result.byte[0] = dstnum.byte[0] + ~srcnum.byte[0] + 1;
                break;
            case XOR:
                result.byte[0] = dstnum.byte[0] ^ srcnum.byte[0];
                break;
            case AND:
                result.byte[0] = dstnum.byte[0] & srcnum.byte[0];
                break;
            case OR:
                result.byte[0] = dstnum.byte[0] | srcnum.byte[0];
                break;
            default:
                printf("invalid\n");
        }
        update_psw(srcnum.byte[0], dstnum.byte[0], result.byte[0], byte);
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

    switch (instr)
    {
        case MOVL:
            regfile[0][DST_reg].byte[0] = B;
            break;
        case MOVLZ:
            regfile[0][DST_reg].byte[0] = B;
            regfile[0][DST_reg].byte[1] = 0;
            break;
        case MOVLS:
            regfile[0][DST_reg].byte[0] = B;
            regfile[0][DST_reg].byte[1] = 0xFF;
            break;
        case MOVH:
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
            // check if bit is 1 or 0, assign status to PSW.Z
            if (bw == word)
            {
                // checks if DST bit is SET or not by shifting a 1 to the desired bit to check and ANDing it with the value to check
                PSW.Z = (regfile[0][DST].word & (1 << temp.word));
            }
            else
            {
                PSW.Z = (regfile[0][DST].byte[0] & (1 << temp.byte[0]));
            }
            break;
        case BIS:
            // set a bit at location temp in DST register
            if (bw == word)
            {
                regfile[0][DST].word |= 1 << temp.word;
            }
            else  // set a bit at location temp in LSByte of DST register
            {
                regfile[0][DST].byte[0] |= 1 << temp.byte[0];
            }
            break;
        case BIC:
            // clear a bit at location temp in DST register
            if (bw == word)
            {
                regfile[0][DST].word &= ~(1 << temp.word);
            }
            else  // clear a bit at location temp in LSByte of DST register
            {
                regfile[0][DST].byte[0] &= ~(1 << temp.byte[0]);
            }
            break;
        default:
            printf("invalid\n");
    }
}

// Load relative from SRC address register + offset to DST (data or address) register
// Store relative from SRC (data or address) register to DST address register + offset
void LDR_STR_instr(enum LDR_STR instr, unsigned short SDRA ,unsigned short OFF, enum SIZE bw, unsigned short SRC, unsigned short DST)
{
    unsigned short EA, mbr;
    switch (instr)
    {
        case LDR:
            // Address reg is the SRC reg for LDR
            EA = (regfile[0][SRC].word | 0x08) + sign_ext(OFF, Bit4);
            if (bw == word)
            {
                bus(EA, &mbr, read, word);
                regfile[0][DST | (SDRA << 3)].word = mbr;
            }
            else  // byte
            {
                bus(EA, &mbr, read, byte);
                regfile[0][DST | (SDRA << 3)].byte[0] = mbr;
            }
            break;
        case STR:
            // Address reg is the DST reg for STR
            EA = (regfile[0][DST].word | 0x08) + sign_ext(OFF, Bit4);
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
void LD_instr(unsigned short DI, unsigned short PRPO, unsigned short ID, enum SIZE bw, unsigned short ADR, unsigned short DST)
{
    unsigned short EA, mbr;

    // ADR is already set to addressing register
    // DST is already set to be data or addressing register

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
                regfile[0][ADR].word = (bw == word)? regfile[0][ADR].word + 2 : regfile[0][ADR].byte[0] + 1;
            }
            else  // decrement
            {
                regfile[0][ADR].word = (bw == word)? regfile[0][ADR].word - 2 : regfile[0][ADR].byte[0] - 1;
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
            regfile[0][ADR].word = (bw == word)? regfile[0][ADR].word + 2 : regfile[0][ADR].byte[0] + 1;
        }
        else  // decrement
        {
            regfile[0][ADR].word = (bw == word)? regfile[0][ADR].word - 2 : regfile[0][ADR].byte[0] - 1;
        }
    }
}

// Store from SRC (data or address) register to DST address register
void ST_instr(unsigned short DI, unsigned short PRPO, unsigned short ID, enum SIZE bw, unsigned short SRC, unsigned short ADR)
{
    unsigned short EA, mbr;

    // SRC is already set to be data or addressing register
    // ADR is already set to addressing register

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
                regfile[0][ADR].word = (bw == word)? regfile[0][ADR].word + 2 : regfile[0][ADR].byte[0] + 1;
            }
            else  // decrement
            {
                regfile[0][ADR].word = (bw == word)? regfile[0][ADR].word - 2 : regfile[0][ADR].byte[0] - 1;
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
            regfile[0][ADR].word = (bw == word)? regfile[0][ADR].word + 2 : regfile[0][ADR].byte[0] + 1;
        }
        else  // decrement
        {
            regfile[0][ADR].word = (bw == word)? regfile[0][ADR].word - 2 : regfile[0][ADR].byte[0] - 1;
        }
    }
}
