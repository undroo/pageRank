#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "adjlist.h"
#include "set.h"

typedef struct AdjListNode * Item;

typedef struct AdjListNode {
    char *word;
    Set urls;
    Item next;
} AdjListNode;

typedef struct AdjListRep {
    int nitems;
    Item items;
} AdjListRep;

// Function signatures

AdjList newAdjList();
void disposeAdjList(AdjList);
void insertAdjListNode(AdjList,char *);
void insertAdjListURL(AdjList,char *,char *);
int  inAdjList(AdjList,char *);
int  nAdjList(AdjList);
void showAdjList(AdjList);

static Item newNode(char *);

// newAdjList()
// - create an initially empty Adjacency List
AdjList newAdjList()
{
	AdjList new = malloc(sizeof(AdjListRep));
	assert(new != NULL);
	new->nitems = 0;
	new->items = NULL;
	return new;
}

// disposeAdjList(AdjList)
// - clean up memory associated with Adjacency List
void disposeAdjList(AdjList al)
{
	if (al == NULL) return;
	Item next, curr = al->items;
	while (curr != NULL) {
		next = curr->next;
		disposeSet(curr->urls);
		free(curr->word);
		free(curr);
		curr = next;
	}
}

// insertAdjListNode(AdjList,Str)
// - ensure that Str is in Adjacency List
void insertAdjListNode(AdjList al, char *str)
{
	assert(al != NULL);
	   
	if (inAdjList(al,str)) return; 
	
	Item new = newNode(str);
	al->nitems++;
	
	if (al->items == NULL)
	    al->items = new;
	else
	{
	    	Item curr = al->items, prev;
	    while(curr != NULL)
	    {
	        prev = curr;
	        curr = curr->next;
	    }
	    prev->next = new;
	}
}

// insertAdjListURL
// - add Url to a node containing Word in Adjacency List
void insertAdjListURL(AdjList al, char * word, char * url)
{
    Item curr = al->items;
	while (curr != NULL ) // iterate through words
	{
	    if (!strcmp(curr->word, word)) // find matching word
	        insertInto(curr->urls, url); // insert url 
	    curr = curr->next;
	}
}

// inAdjList(AdjList,Str)
// - check whether Str is contained in Adjacency List
int inAdjList(AdjList al, char *str)
{
	assert(al != NULL);
	
    Item curr = al->items;
	while (curr != NULL ) {
		if (!strcmp(curr->word, str))
		    return 1;
		curr = curr->next;
	}
    return 0;
}

// nAdjList(AdjList)
// - return # elements in Adjacency List
int  nAdjList(AdjList al)
{
	assert(al != NULL);
	return al->nitems;
}

// showAdjList(AdjList)
// - display Adjancency List
void showAdjList(AdjList al)
{	
	if (al->nitems == 0)
		printf("No words\n");
	else
	{
		Item curr;
		curr = al->items;
		while (curr != NULL)
		{
			printf( "%s ", curr->word );
			int n;
			for (n = 0; n < nElems(curr->urls); n++)
			    printf( "%s ", getValue(curr->urls,n));
			curr = curr->next;
			printf( "\n" );
		}
	}
}

// Helper functions

static Item newNode(char *str)
{
	Item new = malloc(sizeof(AdjListNode));
	assert(new != NULL);
	Set urls = newSet();
	assert(urls != NULL);
	new->word = strdup(str);
	new->urls = urls;
	new->next = NULL;
	return new;
}
