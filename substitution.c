#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


bool valid_key(string key);

int main(int argc, string argv [])
{
    // Check wheter the arrey at the comand line has only one character
    string key = argv [1];
    // Check wheter we have a valid key
    if (argc != 2 || valid_key(key) == false)
    {
        //if its not a valid key print the following
        printf("Usage: ./substitution key(all of the letters in the alphabet in diferent order and without spaces in between\n");
        return 1;
    }
    else
    {
        // If we have a valid key get the srting plain text
        string plaintext = get_string("plaintext: ");

        // Check out how long the plain text is
        int l = strlen(plaintext);
        int k;
        // Turn the key given by usser to upper case
        for (k = 0; k < 25; k++)
        {
            key [k] = toupper(key [k]);
        }

        // Print the ciphertext
        int p;
        printf("ciphertext: ");

        for (p = 0; p < l ; p++)
        {
            //print the upper case letters modified
            if (isalpha(plaintext [p]) && isupper(plaintext [p]))
            {
                k = (plaintext [p]) - 65;
                printf("%c", key [k]);
            }
            //print the lower case letters modified
            else if (isalpha(plaintext [p]) && islower(plaintext [p]))
            {
                k = plaintext [p] - 97;
                printf("%c", key [k] + 32);
            }
            //print other type of characters
            else
            {
                printf("%c", plaintext [p]);
            }
        }
        // Print \n
        printf("\n");
    }
}

// check if we have a correct imput, return true if we do have one
bool valid_key(string key)
{
    // Check if the key has 26 letters
    if (strlen(key) != 26)
    {
        //return false if it hasn´t, it will end the program and print a ussage sign in main
        return false;
    }
    else
    {
        //set a variable called letter with 26 chars
        char letter [26];
        int nk = 0;
        //asign a letter of the alphabet starting with 0 equals a to variable 25 equals z
        for (int a = 0; a < 26; a++)
        {
            letter [a] = 65 + a;
        }
        int i = 0;
        int no = 0;
        //Check that every letter in the alphabet is included in the key
        while (no < 26)
        {
            no = 0;
            for (int b = 0; b < 26 ; b++)
            {
                if (letter [i] == key [b] || letter [i] + 32 == key [b])
                {
                    i++;
                    nk++;
                }
                else
                {
                    //If theres a letter that isn´t there it will give 25 no ande end the while formula
                    no++;
                }

            }
        }
        //If the while formula is ended and the number of nk (letters found) is different from 26 there is a letter missing
        if (nk != 26)
        {
            //returning false will return 1 in main, because we have an invalid key
            return false;
        }
        else
        {
            //returning tru will run the rest of the program
            return true;
        }
    }
}