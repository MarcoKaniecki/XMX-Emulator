//
// Created by Marco Kaniecki on 2022-06-05.
//
#include "emulator.h"

union word_byte srcnum, dstnum;


void SWPB_instr(unsigned short DST)
{
    union word_byte temp;

    temp.byte[0] = regfile[0][DST].byte[0];
    regfile[0][DST].byte[0] = regfile[0][DST].byte[1];
    regfile[0][DST].byte[1] = temp.byte[0];
}


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


void SWAP_instr(unsigned short SRA, unsigned short DRA, unsigned short SRC, unsigned short DST)
{
    union word_byte temp = regfile[0][DST | DRA << 3];

    regfile[0][DST | DRA << 3].word = regfile[0][SRC | SRA << 3].word;
    regfile[0][SRC | SRA << 3].word = temp.word;
}


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
            regfile[0][DST_reg].byte[1] = 0xFF;
            break;
        default:
            printf("invalid instr\n");
    }
}


void MOV_instr(unsigned short SRA, unsigned short DRA, enum SIZE bw, unsigned short SRC, unsigned short DST)
{
    if (bw == word)
    {
        regfile[0][DST | DRA << 3].word = regfile[0][SRC | SRA << 3].word;
    }
    else
    {
        regfile[0][DST | DRA << 3].byte[0] = regfile[0][SRC | SRA << 3].byte[0];
    }
}


void SXT_instr(unsigned short DST)
{
    regfile[0][DST].byte[0] = sign_ext(regfile[0][DST].byte[0], BIT7);
}


void SRAorRRC_instr(enum SRAorRRC instr, enum SIZE bw, unsigned short DST)
{
    union word_byte temp;

    if (instr == SRA)
    {
        PSW.C = EXTR_BIT(regfile[0][DST].word, BIT0);
        if (bw == word)
        {
            temp.word = EXTR_BIT(regfile[0][DST].word, BIT15);
            regfile[0][DST].word = (regfile[0][DST].word >> 1) | (temp.word << 15);
        }
        else
        {
            temp.byte[0] = EXTR_BIT(regfile[0][DST].byte[0], BIT7);
            regfile[0][DST].byte[0] = (regfile[0][DST].byte[0] >> 1) | (temp.byte[0] << 7);
        }
    }
    else  // RRC
    {
        temp.word = PSW.C;
        PSW.C = EXTR_BIT(regfile[0][DST].word, BIT0);
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


void BIx_instr(unsigned short instr, unsigned short RC, enum SIZE bw, unsigned short SC, unsigned short DST)
{
    union word_byte temp = regfile[RC][SC];
    switch (instr)
    {
        case BIT:
            if (bw == word)
            {
                PSW.Z = (temp.word == 0)? 1 : 0;
            }
            else
            {
                PSW.Z = (temp.byte[0] == 0)? 1 : 0;
            }
            break;
        case BIS:
            if (bw == word)
            {
                // regfile[0][DST].word = regfile[0][DST].word & (1 << )
            }
            break;
        case BIC:
            break;
        default:
            printf("invalid\n");
    }
}


