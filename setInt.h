// set.h ... interface to simple Set of Strings
// Written by John Shepherd, September 2015

#ifndef SETINT_H
#define SETINT_H

typedef struct SetIntRep *SetInt;

// Function signatures

SetInt newSetInt();
void disposeSetInt(SetInt);
void insertIntoInt(SetInt,int);
int  isElemInt(SetInt,int);
int  nElemsInt(SetInt);
void showSetInt(SetInt);
int  getValueInt(SetInt,int);
int  findNodeInt(SetInt,int);

#endif
