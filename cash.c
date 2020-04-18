#include <cs50.h>
#include <stdio.h>
#include <math.h>


int main (void)
{
//Ask how much change you have to give away
float change;  
   do
   {
        change = get_float("change: ");
   }
    while (change < 0);
    //Set coins to 0 so we can start counting how many coins we are giving
    int coins = 0;
    //Set change to an int variable type and multiply 100 times to avoid mistakes
  int k = round (change * 100);
  
    printf("%i \n", k);
        //Start discounting, first 25 cents then 10 then 5 then 1
          for(coins = 0; k >= 25; coins++) 
                {
                    k = k-25;
                }
                printf("%i \n", k);
                printf("%i \n", coins);
                while (k >= 10) 
                {
                    k = k-10;
                    coins++;
                }
                while (k >= 5) 
                {
                    k = k-5;
                    coins++;
                }
                while (k >= 1) 
                {
                    k = k-1;
                    coins++;
                }
            
            printf("%i \n", coins);
      
}
