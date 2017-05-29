#ifndef SET_H
#define SET_H

typedef struct SetRep *Set;

// Function signatures

Set newSet();
void disposeSet(Set);
void insertInto(Set,char *);
int  isElem(Set,char *);
int  nElems(Set);
void showSet(Set);
char *getValue(Set, int);

#endif
