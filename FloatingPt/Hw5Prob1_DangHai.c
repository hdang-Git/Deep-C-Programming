/*
 * This program prints out -f and if f is NaN, then it just returns the input f. 
 * assumptions: 32 bit word length
 */


#include <stdio.h>

typedef unsigned float_bits;

/* Compute -f. If f is NaN, then return f. */
float_bits float_negate(float_bits f);


/********************************************************************************************
 * This function calls the float_negate function for all 2^32 values and outputs in hex.    *
 ********************************************************************************************/
int main()
{

   float_bits i;
   for(i = 0; i <=  4294967296; i++)
       printf("Value: %d, Comp. Value: 0x%08x  float_negate Value: 0x%08x\n",i, i, float_negate(i));
   return 0;
}

/******************************************************************************************** 
 * This function returns the same input if it's NaN, else it flips the sign bit of the      *
 * sign and returns the floating point representation.                                      * 
 ********************************************************************************************/
float_bits float_negate(float_bits f){
    unsigned sign = f >> 31;
    unsigned exp = (f >> 23) & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if(exp == 0xFF && frac != 0)		//if NAN
    {
        return f;
    } 
    sign = ~f;
    return (sign << 31)|(exp << 23) | frac;
}
