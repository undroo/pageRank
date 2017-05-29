//Set functions



#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "set.h"

typedef struct Node {
	char *urlName;
	int urlNum;
	list *next;
} Node;

typedef struct SetRep {
	int elems;	
	Node urlList;
	Node cur; 
} SetRep;

Set newSet();
void insertInto(Set, char *);

Set newSet()
{
	Set new = malloc(sizeof(SetRep));
	assert(new != NULL);
	new->elems = 0;
	new->urlList = NULL;
	new->cur = NULL;
	return new;
}

void insertInto(Set S, char *string)
{	
	assert(s != NULL);
	s->elems++;
	
	list curr, prev;
	list new = newNode(string);
	new->urlNum = S->elems;
	
	if (S->first != NULL){
		S->urlList = new;
		S->cur = new;
	} else {
		S->cur->next = new;
	}
	
}

void freeSet(Set S)
{
	if (s == NULL) return;
	list next, curr = S->urlList;
	while (curr != NULL) {
		next = curr->next;
		free(curr->urlName);
		free(curr);	
		curr = next;
	}
	free(S);
}


//Helper Functions


static list newNode(char *url)
{
	Node new = malloc(sizeof(Node));
	assert(new != NULL);
	new->urlNum = 0;
	new->urlName = strdup(url);
	new->next = NULL;
	return new;
}
