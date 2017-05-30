#ifndef ADJLIST_H
#define ADJLIST_H

typedef struct AdjListRep *AdjList;

AdjList newAdjList();
void disposeAdjList(AdjList);
void insertAdjListNode(AdjList,char *);
void insertAdjListNodeAlpha(AdjList,char *);
void insertAdjListURL(AdjList,char *,char *);
int  inAdjList(AdjList,char *);
int  nAdjList(AdjList);
void showAdjList(FILE *,AdjList);
Set getSet(AdjList,char *);

#endif
