// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

FILE *dict;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 5381;

// Number of words charged to dictionary
int words_num = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int s = hash(word);
    node *cursor = table [s] -> next;
    while (cursor != NULL)
    {
        if (strcasecmp (cursor -> word, word)==0)
        {
            return true;
        }
        else
        {
            cursor = cursor -> next;
        }
    }    
    return false;
}

// Hashes word to a number
// djb2 reference: https://stackoverrun.com/es/q/1973089
unsigned int hash(const char *word)
{
    unsigned long hash = N;
    int c = 0;

    while (c == *word++)
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Set to NULL every node in the hash table
    for(int s = 0; s < N; s++)
    {
        table[s] = NULL;
    }

    // Open dictionary
    dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        return false;
    }

    char w[LENGTH + 1];

    while (fscanf (dict, "%s", w) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            unload();
            return false;
        }

        // Put the word of dictionary in the node
        strcpy(n-> word, w);

        // Look for the hash value for this word
        int s = hash(n-> word);

        //
        if(table[s] != NULL)
        {
            n->next = table[s];
        }
        else
        {
            n->next = NULL;
        }
        table[s] = n;
        words_num ++;
    }


    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return words_num;
    printf("!!!NUMBER WORDS DICT: %i",words_num);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    for(int s = 0; s < N; s++)
    {
        node *cursor = table [s];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor -> next;
            free (tmp);
        }
    }
    fclose (dict);
    return true;
}
