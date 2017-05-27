// invertedIndex.c
// Written by Michelle Seeto (5061204)
// Assignment 2 COMP1927 S1,17

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "invertedIndex.h"
#include "set.c"
#include "readData.h"

#define BUFFSIZE 1024

/*

FUNCTIONS THAT ARE REQUIRED:

local:
    - normalise words
    - print inverted list

set.c:
    - getValue
    - insertAlphabetically
    - isInList
    
adjacency list:
    - newAdjList
    - findNode
    
readData.c:
    - findSection

*/

typedef struct AdjListNode *ALNode;

typedef struct AdjListNode {
    char *word;
    Set urls;
    ALNode next;
} AdjListNode;

typedef struct AdjListRep {
    int nitems;
    ALNode items;
} AdjListRep;

// Function signatures

void GetInvertedList(Set);
void normalise(char *)

static ALNode findNode(AList, char *);


// Local functions

void GetInvertedList(Set listOfURLs) {
    char *url
    char word[BUFFSIZE];
    FILE *ptr;
    node wordNode;
    
    AList invertedIndex = newAdjList();
    
    for (int n = 0; n < nElems(listOfURLs); n++)
    {
        url = getValue(URLs,n);
        ptr = fopen(url, "r");
        
        ptr = findSection(2); // skip to section 2
        
        while (!feof(ptr))
        {
            fscanf (ptr, "%s", BUFFSIZE, word);
            if ((wordNode = findNode(invertedIndex,normalise(word))) != NULL)
            {
                if(isInList(
                


// Helper functions

// normalise(char *)
// - transform characters into lowercase
char *normalise(char *word)
{
    char *curr;
    for (curr = word; *curr!='\0'; curr++)
        *curr = tolower(*curr);
    return word;
}

// findNode(AList,char *)
// - find node in List that contains value W
// - return node containing W
// - if no node found, return null
static ALNode findNode(AList list, char *w)
{
    ALNode curr;
    
    for (curr = list->items; curr != NULL; curr = curr->next)
    {
        if (curr->word == w)
            return curr;
    }
    
    return curr;
}        
            
            
            
