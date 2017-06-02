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

static Item newNode(char *);
static int wordcmp(char *p, char *q);


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
	assert(new != NULL);
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

// insertAdjListNodeAlpha(AdjList,Str)
// - insert Str into Adjacency List in alphabetical order
void insertAdjListNodeAlpha(AdjList al, char *str)
{
	assert(al != NULL);
	   
	if (inAdjList(al,str)) return; 
	
	Item new = newNode(str);
    al->nitems++;

	if (al->items == NULL) // list is empty
	    al->items = new;
	
	else // list has items
	{
	    	Item curr = al->items, prev = al->items;
	    while (curr != NULL) // iterate through list until end of list is reached
	    {
	        if (wordcmp(curr->word,str)) // Str goes before current node
	        {
	            if (!strcmp(curr->word,al->items->word)) // insert new node at start of list
	            {
	                new->next = curr;
	                al->items = new;
	                return;
	            }
	            
	            break;
	        }
	        prev = curr;
	        curr = curr->next;
	    }
	    prev->next = new;
	    new->next = curr;
	}
}

// insertAdjListURL
// - add Url to a node containing Word in Adjacency List
void insertAdjListURL(AdjList al, char * word, char * url)
{
    assert(al != NULL);
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
    assert(str != NULL);
	
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
void showAdjList(FILE * ptr, AdjList al)
{	
	assert(al != NULL);
	assert(ptr != NULL);
	if (al->nitems == 0)
		fprintf(ptr, "No words\n");
	else
	{
		Item curr;
		curr = al->items;
		while (curr != NULL)
		{
			fprintf(ptr, "%s ", curr->word );
			int n;
			for (n = 0; n < nElems(curr->urls); n++)
			    fprintf(ptr, "%s ", getValue(curr->urls,n));
			curr = curr->next;
			fprintf(ptr, "\n" );
		}
	}
}

// findAdjListNode(AdjList,char *)
// - iterate through adjacency list until node containing S is found
// - return index of node
// - return -1 if node not found
int  findAdjListNode(AdjList al,char * s)
{
    assert(al != NULL);
    assert(s != NULL);
    Item curr = al->items;
    int n = 0;
    
    while (curr != NULL)
    {
        if (!strcmp(curr->word,s))
            return n;
        n++;
        curr = curr->next;
    }
    return -1;
}

// getSet(AdjList,int)
// - return Set in the nth node
Set  getSet(AdjList al,int n)
{
    assert(al != NULL);
    assert(n < al->nitems);
    
    Item curr = al->items;
    int i;
    for (i = 0; i < n; i++)
        curr = curr->next;

    return curr->urls;
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

// wordcmp(char *,char *)
// - compare words P and Q for alphabetical order
// - if P comes before Q, return 0
// - if Q comes before P, return 1
// - if words are the same, return 0
static int wordcmp(char *p, char *q)
{   
    if (!strcmp(p,q))
        return 0;
    
    while (*p != '\0' && *q != '\0')
    {
        if ((int)(*p) > (int)(*q))
            return 1;
        else if ((int)(*p) < (int)(*q))
            return 0;
        p++;
        q++;
    }
    
    if (*p == '\0')
        return 0;
      
    return 1;
}
