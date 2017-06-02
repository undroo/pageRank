// setInt.h ... interface to simple Set of Ints
// Based off code written by John Shepherd, September 2015

#ifndef SETINT_H
#define SETINT_H

typedef struct SetIntRep *SetInt;

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

#endif
