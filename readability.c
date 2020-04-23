#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);


int main(void)
{
    //get a text from usser
    string text = get_string("Text: ");

    //count number of letters
    int let = count_letters(text);

    //count number of words
    int wor = count_words(text);

    //count number of sentences
    int sen = count_sentences(text);

    double L = 100 * (double) let / (double) wor;
    double S =  100 * (double) sen / (double) wor;

    double colemanliaau = 0.0588 * L - 0.296 * S - 15.8;


    if (colemanliaau < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (colemanliaau > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(colemanliaau));
    }


}

// count number of letters in the text
int count_letters(string text)

{
    int n = 0;
    int letters = 0;

    // loop that counts number of letters (not other characters) till \0 (NUL)
    while (text[n] != '\0')

        // Count lower case
    {
        if (text[n] >= 'a' && text[n] <= 'z')
        {
            n++;
            letters++;
        }

        // Count capital letter
        else if (text[n] >= 'A' && text[n] <= 'Z')
        {
            n++;
            letters++;
        }

        //else don´t count
        else if (text[n] != '\0')
        {
            n++;
        }

    }
    return letters;
}

// count number of words in the text
int count_words(string text)

{
    int n = 0;
    int words = 0;

    // loop that counts number of letters (not other characters) till \0 (NUL)
    while (text[n] != '\0')

        // Count lower case
    {
        if (text[n] >= 'a' && text[n] <= 'z')
        {
            n++;
        }

        // Count capital letter
        else if (text[n] >= 'A' && text[n] <= 'Z')
        {
            n++;
        }

        // If we have a space he should count the first word
        else if (text[n] == ' ')
        {
            n++;
            words++;
        }

        // If we have a dot we start the loop all over
        else if (text[n] != '\0')
        {
            n++;
        }


    }
    if (n > 0)
    {
        words++;
    }
    return words;

}

// count number of sentences in the text
int count_sentences(string text)

{
    int n = 0;
    int sentences = 0;
    int words = 0;

    // loop that counts number of letters (not other characters) till \0 (NUL)
    while (text[n] != '\0')

        // Count lower case
    {
        if (text[n] == '.' || text[n] == '!' || text[n] == '?')
        {
            n++;
            sentences++;
        }


        // If we have a dot we start the loop all over
        else if (text[n] != '\0')
        {
            n++;
        }

    }
    return sentences;


}