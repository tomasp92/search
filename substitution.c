#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


bool is_argv_correct_key(string key);

int main(int argc, string argv [])
{
    // Check wheter the arrey at the comand line has only one character
    string key = argv [1];
    if (argc !=2 || is_argv_correct_key(key) == false)
    {
       printf("Usage: ./substitution key(all of the letters in the alphabet in diferent order and without spaces in between\n");
    }
    else
    {
        string plaintext = get_string ("plaintext: ");
        int l = strlen(plaintext);
        int k;
        for (k = 0; k < 25; k++)
        {
            key [k] = toupper(key [k]);
        }
        int p;
        printf("ciphertext: ");
        for (p = 0; p < l ; p++)
        {
            if( isalpha(plaintext [p]) && isupper(plaintext [p]))
            {
                k = (plaintext [p]) - 65;
                printf("%c", key [k]);
            }
            else if (isalpha(plaintext [p]) && islower(plaintext [p]))
            {
                k = plaintext [p] - 97;
                printf("%c", key [k] + 32);
            }
            else
            {
                printf("%c", plaintext [p]);
            }
        }
        printf("\n");
    }
}

// check if we have a correct imput, return true if we do have one
bool is_argv_correct_key(string key)
{
    if (strlen(key)!= 26)
    {
        return false;
    }
    else
    {
        char letter [26];
        int nk = 0;
        for (int a = 0; a < 26; a++)
        {
            letter [a] = 65 + a;
        }
        int i = 0;
        int no = 0;
        while ( no < 26)
        {
             no = 0;
            for(int b = 0; b<26 ; b++)
            {
                if(letter [i] == key [b] || letter [i] + 32 == key [b])
                {
                    i++;
                    nk++;
                }
                else
                {
                    no++;
                }

            }
        }
        if( nk != 26)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}