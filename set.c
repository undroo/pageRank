// set.c ... simple, inefficient Set of Strings
// Based off code written by John Shepherd, September 2015

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "set.h"

typedef struct Node *Link;

typedef struct Node {
	char *val;
	Link  next;
} Node;
	
typedef struct SetRep {
	int   nelems;
	Link  elems;
} SetRep;

// Function signatures

Set newSet();
void disposeSet(Set);
void insertInto(Set,char *);
int  isElem(Set,char *);
int  nElems(Set);
char *getValue(Set,int);

static Link newNode(char *);
static void disposeNode(Link);

// newSet()
// - create an initially empty Set
Set newSet()
{
	Set new = malloc(sizeof(SetRep));
	assert(new != NULL);
	new->nelems = 0;
	new->elems = NULL;
	return new;
}

// disposeSet(Set)
// - clean up memory associated with Set
void disposeSet(Set s)
{
	if (s == NULL) return;
	Link next, curr = s->elems;
	while (curr != NULL) {
		next = curr->next;
		disposeNode(curr);	
		curr = next;
	}
}

// insertInto(Set,Str)
// - ensure that Str is in Set
void insertInto(Set s, char *str)
{
	assert(s != NULL);
	   
	if (isElem(s,str)) return; 
	
	Link new = newNode(str);
	s->nelems++;
	
	
	if (s->elems == NULL)
	    s->elems = new;
	else
	{
	    	Link curr = s->elems, prev;
	    while(curr != NULL)
	    {
	        prev = curr;
	        curr = curr->next;
	    }
	    prev->next = new;
	}
}

// isElem(Set,Str)
// - check whether Str is contained in Set
int isElem(Set s, char *str)
{
	assert(s != NULL);
	
    Link curr = s->elems;
	while (curr != NULL ) {
		if (!strcmp(curr->val, str))
		    return 1;
		curr = curr->next;
	}
    return 0;
}

// nElems(Set)
// - return # elements in Set
int  nElems(Set s)
{
	assert(s != NULL);
	return s->nelems;
}

// showSet(Set)
// - display Set (for debugging)
void showSet(Set s)
{
	Link curr;
	if (s->nelems == 0)
		printf("Set is empty\n");
	else {
		printf("Set has %d elements:\n",s->nelems);
		int id = 0;
		curr = s->elems;
		while (curr != NULL) {
			printf("[%03d] %s\n", id, curr->val);
			id++;
			curr = curr->next;
		}
	}
}

char *getValue(Set s, int n)
{
    int i;
    Link curr = s->elems;
    for (i = 0; i < n; i++)
        curr = curr->next;
    return curr->val;
}

// Helper functions

static Link newNode(char *str)
{
	Link new = malloc(sizeof(Node));
	assert(new != NULL);
	new->val = strdup(str);
	new->next = NULL;
	return new;
}

static void disposeNode(Link curr)
{
	assert(curr != NULL);
	free(curr->val);
	free(curr);
}
