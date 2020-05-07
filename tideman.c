#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        printf("\n");
        record_preferences(ranks);
    }
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();




   
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int a = 0; a < candidate_count; a++)
    {
        if (strcmp(candidates [a], name) == 0)
        {
            ranks [rank] = a;
            return true;
        }


    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        int a = ranks [i];
        for (int j = 0; j < candidate_count; j++)
        {
            int b = ranks [j];
            if (i < j)
            {
                preferences [a][b] ++;
            }


        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int a = -1;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences [i][j] > preferences [j][i])
            {
                a++;
                pairs[a].winner = i;
                pairs[a].loser = j;
            }
        }
    }
    pair_count = a + 1;
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int swap_count = -1;
    while (swap_count != 0)
    {
        swap_count = 0;
        for (int i = 0; i < (pair_count -1); i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i+1].winner][pairs[i+1].loser])
            {
                swap_count++;
                pair a = pairs [i+1];
                pairs [i+1] = pairs [i];
                pairs [i] = a;
            }
        }
    }


    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if(locked [pairs [i].loser] [pairs [i].winner] ==false)
        {
            locked [pairs [i].winner] [pairs [i].loser] = true;
            for (int j = 0; j < pair_count; j++)
            {
                if(locked [j][pairs [i].winner] == true)
                {
                    locked [j][pairs[i].loser] = true;
                }
                else if(locked [pairs [i].loser][j] == true)
                {
                    locked [pairs[i].winner][j] = true;
                }
            }

        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{

    int champeon = 0;
    for (int i = 0; i < pair_count; i++)
    {
        int trues = 0;
        for (int j = 0; j < pair_count; j++)
        {
            if( locked [j][i])
            {
                trues++;
            }
        }

    if(trues == 0)
    {
        champeon = pairs [i].winner;
    }
    }
    printf("%s \n", candidates [champeon]);
}

