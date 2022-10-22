#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
// Implements a dictionary's functionality
#include "dictionary.h"
// Number of buckets in hash table 170953 for quadratic probing
const unsigned int N = 170953;
/* Hash table
Yes, I am leaving you in suspense, but I'm sure you know where this is going! */
// (I also wonder if it's possible/faster to have this arrow in a function to utilize stack speeds)
char table[N][LENGTH + 1];
// Please don't mind our little counter to keep track of our loaded words 🤌
int wordCount = 0;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Let's begin by taking the word and hasing it :D
    int index = hash(word),
        i = 1;
    // Found this after hours of searching and finding just horrible/overly complex hash tables xD
    // https://www.hackerearth.com/practice/data-structures/hash-tables/basics-of-hash-tables/tutorial/
    // Esentially we keep on going to the next item until we find our word or there's nothing left
    while (*table[index] != 0)
    {
        // Not sure if there is a difference from running this after the while loop
        // and checking if it's not equal to -- but I placed it inside so I only
        // execite the function once.
        if (strcasecmp(table[index], word) == 0)
        {
            // If we find the word right off the bat, hip-hip-hurray! 🥳 🎉
            // We have sized the day 😎
            return true;
        }
        index = (index + i * i) % N;
        i++;
    }
    // Otherwise, then we haven't found the word, unfortunately. 😭
    return false;
}
// Hashes word to a number
unsigned int hash(const char *word)
{
    // Adapted from http://stackoverflow.com/questions/2571683/djb2-hash-function.
    // Although we won't be chainning, we still need a lovely hash method.
    // And something about this prime number seems to work
    unsigned long hash = 393241;
    for (const char *ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }
    return hash % N;
}
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // This will load the file dictionary into our string of dictionary.
    FILE *file = fopen(dictionary, "r");
    // This is a bit of an over kill for space of w.
    // But at least I don't have to use slow poke heap memory malloc for it! 🏎💨
    char w[1][LENGTH + 1];
    // We will keep on scanning for as long as there's still something to scan.
    while (fscanf(file, "%s", *w) != EOF)
    {
        // Here we apply the same function that we did in search, but instead
        // assigning a value to any available space.
        int index = hash(*w),
            i = 1;
        // Because global arrays in C are initialized to zero, then we can assume
        // that items within such array are indeed zero for our quadratic probing.
        // Albeit I also don't think quadratic probing makes a noticiable difference 
        // for this Pset. And I also read about a double hashing technique... 
        // ***Spoiler Alert*** --> 🐌
        while (*table[index] != 0)
        {
            index = (index + i * i) % N;
            i++;
        }
        // We copy the word into the array
        strcpy(table[index], *w);
        // We will keep track of the number of words loaded.
        wordCount++;
    }
    // "FREE ATLAST!" said the benevolent dictionary.txt 🤝
    fclose(file);
    return true;
}
// Returns number of words in dictionary if loaded, else 0 if not yet loaded.
unsigned int size(void)
{
    // Given that wordCount is by default zero, we simply just return zero
    // no need for an if else statement.
    return wordCount;
}
// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Because we didn't use malloc for our dictionary,
    // we do not need to free any nodes in a linked list!
    // So cool on how little space and fast performance probing is!! 
    // Admittedly, it initially feels like this is an inefficient way to go at it
    // from how it was discussed in the lectures and the Doug short.
    return true;
}