//Set functions

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "set.h"


typedef  struct Node *list;

typedef struct Node {
	char *urlName;
	list *next;
} Node;

typedef struct SetRep {
	int elems;	
	list urlList;
} SetRep;

Set newSet();
void insertInto(Set, char *);


static Link newNode(char *);

Set newSet()
{
	Set new = malloc(sizeof(SetRep));
	assert(new != NULL);
	new->elems = 0;
	new->urlList = NULL;
	return new;
}

void insertInto(Set S, char *string)
{	
	assert(s != NULL);
	if (S->first != NULL){
		
	} else {
	}
	
}

void freeSet(Set S)
{
	if (s == NULL) return;
	list next, curr = s->urlList;
	while (curr != NULL) {
		next = curr->next;
		free(curr->urlName);
		free(curr);	
		curr = next;
	}
	free(S->first);
}


//Helper Functions

static Link newNode(char *url)
{
	list new = malloc(sizeof(Node));
	assert(new != NULL);
	new->urlName = strdup(url);
	new->next = NULL;
	return new;
}
