#include <cs50.h>
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>

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

        record_preferences(ranks);

        printf("\n");
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

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
// ranks = [1,3, 2, ...]
void record_preferences(int ranks[])
{

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int ith_pref = ranks[i];
            int jth_pref = ranks[j];
            // i is preferred over j
            preferences[ith_pref][jth_pref]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            pair p;
            if (preferences[i][j] > preferences[j][i])
            {
                p.winner = i;
                p.loser = j;
                pairs[pair_count] = p;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                p.winner = j;
                p.loser = i;
                pairs[pair_count] = p;
                pair_count++;
            }

        }
    }


    return;
}

// Sort pairs in decreasing order by strength of victory
// apply qsort, lambda function first.

int lambda(const void *a, const void *b)
{
    pair arg1 = *((const pair *)a);
    pair arg2 = *((const pair *)b);
    int val1 = preferences[arg1.winner][arg1.loser];
    int val2 = preferences[arg2.winner][arg2.loser];
    return val2 - val1; // we need to sort in decreasing order.
}

void sort_pairs(void)
{

    qsort(pairs, pair_count, sizeof(pair), lambda);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles

bool has_cycle_(int ind, bool visited[])
{
    if (visited[ind])
    {
        return true;
    }
    visited[ind] = true;
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[ind][i] == true)
        {
            if (has_cycle_(i, visited) == true)
            {
                return true;
            }

        }
    }
    return false;
}

bool has_cycle(int start)
{
    bool visited[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        visited[i] = false;
    }
    return has_cycle_(start, visited);

}

void lock_pairs(void)
{

    for (int i = 0; i < pair_count; i++)
    {

        locked[pairs[i].winner][pairs[i].loser] = true;
        // check for a cycle
        if (has_cycle(pairs[i].winner))
        {
           locked[pairs[i].winner][pairs[i].loser] = false;
        }

    }
    return;
}

// Print the winner of the election
bool is_root(int node)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][node])
        {
            return false;
        }
    }
    return true;
}

int get_root(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (is_root(i))
        {
            return i;
        }
    }
    return 11;
}
void print_winner(void)
{
    int root = get_root();
    if (root != 11)
    {
        printf("%s\n", candidates[root]);
    }

    return;
}

