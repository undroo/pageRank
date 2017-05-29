// set.h ... interface to simple Set of Strings
// Based off code written by John Shepherd, September 2015

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

#endif
