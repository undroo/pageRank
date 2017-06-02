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

Set GetCollection();
AdjList GetInvertedList(Set);
char *normalise(char *);

int main()
{
    Set s = GetCollection();
    AdjList al = GetInvertedList(s);

    FILE * ptr = fopen("invertedIndex.txt", "w");
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
    
    AdjList invertedIndex = newAdjList();
    
    for (int n = 0; n < nElems(URLlist); n++)
    {
        strcpy(url,getValue(URLlist,n));
        strcpy(fullurl,url);
        ptr = fopen(strcat(fullurl,".txt"), "r");
        assert( ptr != NULL );

        while (strstr(fgets(line, BUFSIZE, ptr), "Section-2") == NULL) { }
        
        while (fscanf(ptr, "%s", word) != EOF)
        {
            if (strstr(word, "#end") != NULL ) break;
            insertAdjListNodeAlpha(invertedIndex,normalise(word));
            insertAdjListURL(invertedIndex,normalise(word),url);
        }
        
        fclose(ptr);
    }
    
    return invertedIndex;
}

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
