// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// N = length of the dictionary / some integer
const unsigned int N = 1000;

// Hash table
node *table[N];

// word counter in the dictionary
unsigned int word_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{

    //hash the word and get the index
    unsigned int ind = hash(word);
   //define a pointer dummy
    node *dummy = table[ind];
    //start compatring
    while(dummy != NULL)
    {
        if (strcasecmp(dummy->word, word) == 0)
        {
            return true;
        }
        dummy = dummy->next;
    }


    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    //reference https://stackoverflow.com/questions/7666509/hash-function-for-string
    unsigned int hash = 5381;
    int c;

    while ((c = tolower(*word++)))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool dict_loaded = false;
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Dictionary did not open\n");
        return false;
    }
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    char word[LENGTH + 1];
    node *v;
    while (fscanf(dict, "%s", word) != EOF)
    {
        // new word
        word_count++;
        // allocate mem for word !
        v = malloc(sizeof(node));
        if (v == NULL)
        {
            unload();
            fclose(dict);
            return false;
        }
        // copy the word from the dict  to v.word
        strcpy(v->word, word);
        // hash the word to get the index ind for the table
        unsigned int ind = hash(v->word);
        // insert the new node into the linked list


        if (table[ind] == NULL)
        {
            table[ind] = v;
            v->next = NULL;
        }
        else
        {
            v->next = table[ind];
            table[ind] = v;
        }

    }
    fclose(dict);
    dict_loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{

    // counting has been done in the load function
    if (dict_loaded)
        return word_count;
    else
        return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    // if the dict is not loaded then return false
    if (!dict_loaded)
        return false;
    // else iterate over the table and free all the allocated memory
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor =  cursor->next;
            free(tmp);
        }

    }
    return true;
}
