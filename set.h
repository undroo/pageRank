//set.h
//Based off code written by John Shepherd, September 2015



typedef struct SetRep *Set;

Set newSet();
void disposeSet(Set);
void insertInto(Set,char *);
//void dropFrom(Set,char *);
//int  isElem(Set,char *);
//int  nElems(Set);
//void showSet(Set);


