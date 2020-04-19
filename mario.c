#include <cs50.h>
#include <stdio.h>

int main(void)
{
// Ask the user the height int between 1 and 8
    int H; 
    do
    {
        H = get_int("Heigh between 1 and 8: ");
    }
    while (H < 1 || H > 8);
// Print space bars and count them in a inverse way than hashs
    for (int i = 1; i <= H; i++)
    {
        for (int j = 0; j < 1 * H - i ; j++)
        {
            printf(" ");
        }
        //Print the hashs
        for (int j = 0; j < 1 * i ; j++)
        {    
            printf("#");
        }
            printf("  ");
        {
              for (int j = 0; j < 1 * i ; j++)
            printf("#");
            printf("\n");
        
        }
    }        
}
