// Implements a dictionary's functionality
#include "dictionary.h"
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1145;

// Hash table
node *table[N];
int wordCount = 0;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *cursor = table[index];
    while (cursor != NULL && strcasecmp(word, cursor->word) != 0)
    {
        cursor = cursor->next;
    }
    if (cursor == NULL)
    {
        return false;
    }
    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int i = 0, sum = 0, power = 1;
    while (word[i] != '\0')
    {
        sum += tolower(word[i]) * power;
        power *= 3;
        i++;
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char buffer[LENGTH];
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        printf("Could not open\n");
        return false;
    }

    while (fscanf(input, "%s", buffer) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Its a null pointer\n");
            return false;
        }
        strcpy(n->word, buffer);
        int index = hash(n->word);
        n->next = table[index];
        table[index] = n;
        wordCount++;
    }

    fclose(input);
    size();
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (wordCount > 0)
    {
        return wordCount;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp;
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
