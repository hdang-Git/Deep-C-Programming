/*
 * This program converts integers to floats using bi-level floating-point coding rules.
 * For relatively large numbers, the float value of the union still displays 0 because of some    
 * undefined behavior.
 */

#include <stdio.h>

/* Access bit-level representation floating-point number */
typedef unsigned float_bits;

//func prototype
float_bits float_i2f(int i);

//data structure
union fPres
{
    int i;
    float_bits fb;
};


/********************************************************************************************
 * This function calls the i2f() function and prints out the converted value by using the   *
 * union.
 ********************************************************************************************/
int main()
{
   
   union fPres fVar;
   fVar.i = 15213; //2099901000;
   printf("\nnum casted should be %f\n", (float)(fVar.fb));
   fVar.fb = float_i2f((int) fVar.i);
   printf("num after call in hex is %x\n", fVar.fb);
   printf("\nConversion in floating point is %f\n", (fVar.fb)); 
   return 0;
}

/********************************************************************************************
 * This function breaks down the input integer into its sign, exponent, and significand     *
 * component. After which, it rounds according to the IEEE754 conventions.                  *
 ********************************************************************************************/

float_bits float_i2f(int i)
{
   unsigned sign;
   unsigned exp;
   unsigned frac;

   //Check sign of i and get magnitude
   //sign = (i >= 0) ? 0 : 1;
   if ( i >= 0)
      sign = 0;
   else 
   {
      sign = 1;
      i = ~i + 1; //two's complement
   }

   unsigned Bias_Norm = 127;  //w = 32, 2^(8-1) - 1 = 127
   unsigned e = 0;
   //Get the exponent value by making a counter
   float_bits binNum = i;
   printf("num: %08x    sign: %x\n", i, sign);
   while (binNum > 1)
   {  
      binNum = binNum >> 1;
      e++;
   }
   printf("e counter: %08u\n", e);
   printf("binNum is now: %08u\n", binNum);
   //Get the exponent representation
   exp = (e + Bias_Norm);
   printf("exp: # %u    0x%x\n", exp, exp);	


   //Get the fractional part aka signficand
   frac = (((i << 32 - e) >> 1) & 0x7FFFFFFF) >> 8;
   printf("frac: #%d    %08x\n\n", frac, frac);

   //Output 
   printf("\n\nSIGN:     0x%x\n", sign);
   printf("EXPONENT: 0x%x\n", exp);
   printf("FRACTION: 0x%x\n", frac); 
   //Store floating-point representation
   float_bits fNum = (sign << 31) | (exp << 23) | frac;
   printf("NUM     : 0x%x\n\n\n", fNum);
   //Store mantissa
   unsigned mantissa = (fNum & 0x00FFFFFF)|0x00FFFFFF;
   printf("mantissa: 0x%08x\n", mantissa);


   //rounding       
   unsigned temp;
   if (e > 23)
   {
      temp = (i << (33-e)); //shift to get 1 fractional bit and the bits thrown off in msb
      if((temp & 0x70000000) == 0x40000000) //if at midpt
      {   
         printf("At the midpt\n");
         if((temp & 0x80000000) == 0x80000000)
         {  printf("lsb is odd\n");
            frac += 0x01;
         }else 			//temp & 0x8000000 = 0x0000000
            printf("lsb is even\n");
      } else if((temp & 0x70000000) > 0x40000000) {    //if greater than the midpt
         printf("I'm greater than the midpt\n");
         frac += 0x01;
      } else                                           //less than the midpt
          printf("I'm lower than the midpt\n");  
      
   }
   //if num does not overflow fraction with e > 23, then leave it as is. 

   printf("\n\n\nNew Final NUM     : 0x%x\n\n\n", fNum);

   return (sign << 31) | (exp << 23) | frac;
}


