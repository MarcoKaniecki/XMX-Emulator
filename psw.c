//
// Created by Marco Kaniecki on 2022-06-03.
//
// psw.c

#include "emulator.h"

unsigned carry[2][2][2] = {0,0,1,0,1,0,1,1};
unsigned overflow[2][2][2] = {0,1,0,0,0,0,1,0};

psw PSW;

// Update the PSW bits (V, N, Z, C)
// using src, dst, and res values and whether word or byte
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
}

// special update psw func for BIS and BIC since having them with the rest caused an overflow to be set
// when BIS and BIC could never trigger overflow (or carry)
void update_psw_BIS_BIC(unsigned short res, unsigned short wb)
{
    unsigned short msbres;  // most significant bits for src, dst, and res

    if (wb == 0)  // word
        msbres = BIT15(res);
    else  // byte
    {
        msbres = BIT7(res);
        res = res & 0xFF;  // mask high byte
    }

    // Zero
    PSW.Z = (res == 0);
    // Negative
    PSW.N = (msbres == 1);
}