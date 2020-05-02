#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int a = 0; a < candidate_count; a++)
    {
        if (strcmp(candidates [a].name, name) == 0)
        {
            preferences [voter][rank] = a;
            return true;
        }


    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // set counter for all the voters
    int i = 0;
    for (i = 0; i < voter_count; i++)
    {
        int j = 0;
        int c = -1;
        // while we don´t find the candidate that in the preference [i] [j] was voted
        while (preferences [i][j] != c)
        {
            c++;
            // if we find it give him that vote, if it is not eliminated
            if (preferences [i][j] == c && !candidates[c].eliminated)
            {
                candidates[c].votes++;
            }
            // if it is eliminated already sum one to preferences to se the next candidate in that voters list
            else if (preferences [i][j] == c && candidates[c].eliminated)
            {
                j++;
                c = -1;
            }
        }
    }
}


// Print the winner of the election, if there is one
bool print_winner(void)
{
    // check the max number of votes
    int maxvote = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > maxvote)
        {
            maxvote = candidates[i].votes;
        }

    }

    // print the candidate that have the max number of votes and that has more than half the vote
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == maxvote && maxvote > voter_count / 2)
        {
            printf("%s\n", candidates [i].name);
            return true;
        }

    }
    return false;


}

// Return the minimum number of votes any remaining candidate has
// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // check the number of people that are still in election
    int n = 0;
    for (int b = 0; b < candidate_count; b++)
    {
        if (!candidates[b].eliminated)
        {
            n++;
        }
    }
    // check are they still in election and create an array with people that are in
    int sc_votes [n];
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            sc_votes [i] = candidates[i].votes;
        }
    }
    // check the max number of votes
    int maxvote = 0;
    for (int a = 0; a < n; a++)
    {
        if (sc_votes[a] > maxvote)
        {
            maxvote = sc_votes [a];
        }

    }
    // check the min number of votes
    int minvote = maxvote;
    for (int j = 0; j < n; j++)
    {
        if (sc_votes[j] < minvote)
        {
            minvote = sc_votes [j];
        }

    }
    
    //return the minimum amount of votes
    return minvote;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // check the number of people that are still in election
    int n = 0;
    for (int b = 0; b < candidate_count; b++)
    {
        if (!candidates[b].eliminated)
        {
            n++;
        }
    }
    // check are they still in election and create an array with people that are in
    int sc_votes [n];
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            sc_votes [i] = candidates[i].votes;
        }
    }
    // Set variable c to count how manny candidates have the same amount of votes
    int c = 0;
    // check out wich of remaining candidates has min votes
    for (int a = 0; a < n; a++)
    {
        if (sc_votes[a] == min)
        {
            c++;
        }
    }
    // If c == n it means its a tie and we return true
    if (c == n)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (min == candidates[i].votes)
        {
            candidates[i].eliminated = true;
        }
    }
    
    return;
}
