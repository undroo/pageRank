// inverted.c
// Written by Michelle Seeto (5061204)
// Assignment 2 COMP1927 S1,17

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "set.h"
#include "adjlist.h"
#include "ReadData.h"
#include "setInt.h"

#define BUFSIZE 1024

AdjList GetInvertedList(Set);
char *normalise(char *);

int main()
{
    Set s = GetCollection(); // get urls from collection.txt
    AdjList al = GetInvertedList(s); // make an inverted list from the given urls

    FILE * ptr = fopen("invertedIndex.txt", "w"); // print the adjacency list to a text file
    assert( ptr != NULL );
    showAdjList(ptr,al);
    
    fclose(ptr);
    disposeSet(s);
    disposeAdjList(al);
    
    return 0;
}
    

AdjList GetInvertedList(Set URLlist) {
    char url[BUFSIZE];
    char fullurl[BUFSIZE];
    char word[BUFSIZE];
    char line[BUFSIZE];
    FILE *ptr;
    
    AdjList invertedIndex = newAdjList(); // create empty adjacency list
    
    for (int n = 0; n < nElems(URLlist); n++) // iterate through url list
    {
        strcpy(url,getValue(URLlist,n)); // copy url from list to "url" string
        strcpy(fullurl,url); // copy from "url" string to "fullurl" string
        ptr = fopen(strcat(fullurl,".txt"), "r"); // add ".txt" to the end of fullurl, then open given text file
        assert( ptr != NULL );

        while (strstr(fgets(line, BUFSIZE, ptr), "Section-2") == NULL) { } // scan line by line until section 2
        
        while (fscanf(ptr, "%s", word) != EOF) // scan word by word until end of file
        {
            if (strstr(word, "#end") != NULL ) break; // if end of section 2 is reached, break out of fscanf
            insertAdjListNodeAlpha(invertedIndex,normalise(word)); // create a node for each (new) word in text file
            insertAdjListURL(invertedIndex,normalise(word),url); // add url to the set of given word
        }
        
        fclose(ptr);
    }
    
    return invertedIndex;
}

// normalise(char *)
// - normalise words by making everything lowercase and omitting punctuation (except for hyphens)
char *normalise(char *word)
{
    char *url;
    url = word;
    while (*url != '\0')
    {
        *url = tolower(*url);
        if (!((*url >= 'a' && *url <= 'z') || (*url >= '0' && *url <= '9') || *url == '-'))
        {
            *url = '\0';
            break;
        }
        url++;
    }

    return word;
}
