#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "set.h"

typedef struct AdjListRep *AdjList;

AdjList newAdjList();
void disposeAdjList(AdjList);
void insertAdjListNode(AdjList,char *);
void insertAdjListURL(AdjList,char *,char *);
int  inAdjList(AdjList,char *);
int  nAdjList(AdjList);
void showAdjList(FILE *,AdjList);
