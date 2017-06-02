// setInt.c ... simple, inefficient Set of Ints
// Based off code written by John Shepherd, September 2015

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "setInt.h"

typedef struct Node *Link;

typedef struct Node {
	int   val;
	Link  next;
} Node;
	
typedef struct SetIntRep {
	int   nelems;
	Link  elems;
} SetIntRep;

// Function signatures

SetInt newSetInt();
void disposeSetInt(SetInt);
void insertIntoInt(SetInt,int);
void insertAfterInt(SetInt, int, int);
int  isElemInt(SetInt,int);
int  nElemsInt(SetInt);
void showSetInt(SetInt);
int  getValueInt(SetInt,int);
int  findNodeInt(SetInt,int);
int  getInt(SetInt);

static Link newNode(int);
static void disposeNode(Link);

// newIntSet()
// - create an initially empty Set
SetInt newSetInt()
{
	SetInt new = malloc(sizeof(SetIntRep));
	assert(new != NULL);
	new->nelems = 0;
	new->elems = NULL;
	return new;
}

// disposeSet(Set)
// - clean up memory associated with Set
void disposeSetInt(SetInt s)
{
	if (s == NULL) return;
	Link next, curr = s->elems;
	while (curr != NULL) {
		next = curr->next;
		disposeNode(curr);	
		curr = next;
	}
}

// insertIntoInt(SetInt,Str)
// - insert Str onto the end of set S
void insertIntoInt(SetInt s, int n)
{
	assert(s != NULL);
	
	Link new = newNode(n);
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

// insertAfterInt(SetInt,int)
// - insert number I into set after node containing N
void insertAfterInt(SetInt s, int i, int n)
{
    Link curr = s->elems;
    Link new = newNode(i);
    s->nelems++;
    
    while (curr != NULL)
    {
        if (curr->val == n)
        {
            new->next = curr->next;
            curr->next = new;
        }
        curr = curr->next;
    }
}

// isElemInt(Set,n)
// - check whether n is contained in Set
int isElemInt(SetInt s, int n)
{
	assert(s != NULL);
	
    Link curr = s->elems;
	while (curr != NULL ) {
		if (curr->val == n)
		    return 1;
		curr = curr->next;
	}
    return 0;
}

// nElemsInt(Set)
// - return # elements in Set
int  nElemsInt(SetInt s)
{
	assert(s != NULL);
	return s->nelems;
}

// showSet(Set)
// - display Set (for debugging)
void showSetInt(SetInt s)
{
	Link curr;
	if (s->nelems == 0)
		printf("Set is empty\n");
	else {
		printf("Set has %d elements:\n",s->nelems);
		int id = 0;
		curr = s->elems;
		while (curr != NULL) {
			printf("[%03d] %d\n", id, curr->val);
			id++;
			curr = curr->next;
		}
	}
}

// getValueInt(SetInt,int)
// - return value of nth element
int getValueInt(SetInt s, int n)
{
    if (n >= nElemsInt(s))
    	    return 0;

    int i;
    Link curr = s->elems;
    for (i = 0; i < n; i++)
        curr = curr->next;
    return curr->val;
}

// findNode(Set,int)
// - iterate through set to find node containing N
// - return index of node
// - return -1 if node not found
int findNodeInt(SetInt s, int n)
{
    Link curr = s->elems;
    int i = 0;
    while (curr != NULL)
    {
        if (curr->val == n)
            return i;
        curr = curr->next;
        i++;
    }
    return -1;
}

// getInt(SetInt)
// - return an the first int that is not in the set
// - assumes that values go from 1...n, where n is the number is items in a set
// - return 0 if all values are taken
int  getInt(SetInt s)
{
    int i;
    Link curr = s->elems;
    for (i = 1; i <= nElemsInt(s); i++)
    {
        while (curr != NULL)
        {
            if (curr->val == i)
                break;
            else
                curr = curr->next;
        }
        if (curr == NULL)
            return i;
    }
    return 0;
}

// Helper functions

static Link newNode(int n)
{
	Link new = malloc(sizeof(Node));
	assert(new != NULL);
	new->val = n;
	new->next = NULL;
	return new;
}

static void disposeNode(Link curr)
{
	assert(curr != NULL);
	free(curr);
}
