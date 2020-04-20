#include <cs50.h>
#include <stdio.h>
#include <math.h>


int main(void)
{

//Ask a positive credit card number
    long number;  
    do
    {
        number = get_long("number: ");
    }
    while (number < 0);
      // Extract all the digits
      int a16 = (number % 10); 
      int a15 = (number % 100 - a16 )/10;
      int a14 = (number % 1000 - a15)/100;
      int a13 = (number % 10000 - a14)/1000; 
      int a12 = (number % 100000 - a13)/10000;
      int a11 = (number % 1000000 - a12)/100000;
      int a10 = (number % 10000000 - a11)/1000000;
      int a9 = (number % 100000000 - a10)/10000000;
      int a8 = (number % 1000000000 - a9)/100000000;
      int a7 = (number % 10000000000 - a8)/1000000000;
      int a6 = (number % 100000000000 - a7)/10000000000;
      int a5 = (number % 1000000000000 - a6)/100000000000;
      int a4 = (number % 10000000000000 - a5)/1000000000000;
      int a3 = (number % 100000000000000 - a4)/10000000000000; 
      int a2 = (number % 1000000000000000 - a3)/100000000000000;
      int a1 = (number % 10000000000000000 - a2)/1000000000000000;
      //multiply every other digit by 2 
      int b15 = ( a15 * 2)% 10;
      int c15 = (a15*2 % 100 - b15 )/10;
      int b13 = ( a13 * 2)% 10;
      int c13 = (a13*2 % 100 - b13 )/10;
      int b11 = ( a11 * 2)% 10;
      int c11 = (a11*2 % 100 - b11 )/10;
      int b9 = ( a9 * 2)% 10;
      int c9 = (a9*2 % 100 - b9 )/10;
      int b7 = ( a7 * 2)% 10;
      int c7 = (a7*2 % 100 - b7 )/10;
      int b5 = ( a5 * 2)% 10;
      int c5 = (a5*2 % 100 - b5 )/10;
      int b3 = ( a3 * 2)% 10;
      int c3 = (a3*2 % 100 - b3 )/10;
      int b1 = ( a1 * 2)% 10;
      int c1 = (a1*2 % 100 - b1 )/10;
      //check if the sum is iqual to twenty
      int num20 = (a16 + b15 + c15 + a14 + b13 + c13 + a12 + b11 + c11 + a10 + b9 + c9 + a8 + b7 + c7 + a6 + b5 + c5 + a4 + b3 + c3 + a2 + b1 + c1) % 10;
    //If it gives a numer wich isn´t aproved by Luhn´s Algorithm say invalid 
    if ( num20 > 0 )
    {
        printf("INVALID\n");
    }

        //check out if its a valid VISA
    else if ( 3999999999999 < number && 5000000000000 > number) 
    {
        printf("VISA\n");  
    }
     else if (3999999999999999 < number && 5000000000000000 > number) 
    {
        printf("VISA\n");  
    }
    //check out if its a valid Master Mard
    else if (5099999999999999 < number && 5600000000000000 > number)
    {
        printf("MASTERCARD\n");
    }    
    //checkout if its a valid American Express
    else if (339999999999999 < number && 350000000000000 > number)
    {
        printf("AMEX\n");
    }
     else if (369999999999999 < number && 380000000000000 > number)
    {
        printf("AMEX\n");
    }
    else 
    {
        printf("INVALID\n");
    }
   
    
}

