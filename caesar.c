#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool isargvanumber(string key);


int main(int argc, string argv [])

{
    // Check wheter te arrey at the comand line has only one character
    if (argc == 2)
    {
        // Check wheter te arrey is a number
        string key = argv [1];
        if (isargvanumber(key) == true)
        {
             //If its not print the following
             printf("Usage: ./caesar key\n");
             return 1;
        }
        //If it is a number transforme the string into a int
        else
        {
            int k = atoi(key);

            //get a text to encipher
            string plaintext = get_string("plaintext: ");

            //Encipher the text
            int a = 0;
            string ciphertext [a];
            printf("ciphertext: ");

            while (plaintext [a] != '\0')
            {
               // check wether its a lower case and transform it
               if (isalpha(plaintext [a]) && islower(plaintext [a]))
               {
                  printf("%c", (plaintext [a] - 97 + k) % 26 + 97);
               }
               // check wether its a upper case and transform it
               else if (isalpha(plaintext [a]) && isupper(plaintext [a]))
               {
                  printf("%c", (plaintext [a] - 65 + k) % 26 + 65);
               }
               // else live it as it is
               else
               {
                  printf("%c", plaintext [a]);
               }
               a++;
            }

      printf("\n");

      }
    }
    // In case ut has more than one character print the following
    else
    {
       printf("Usage: ./caesar key\n");
       return 1;
    }
}

// Check wheter the arrey is a number

bool isargvanumber(string key)
{
   int n = 0;
   int nk = 0;
   // Check that every char in the arrey is a number
   while (key [n] != '\0')
   {
      if (key [n] > '9' || key[n] < '0')

      {
         n++;
         nk++;
      }
      else
      {
         n++;
      }

   }
    // return true if every char in te arrey its a number
    if (nk > 0)
    {
        return true;
    }
    else
    {
        return false;
    }

}

