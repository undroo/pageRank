#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "setInt.h"
#include "set.h"

#define BUFSIZE 1024
#define MAXURL 100

int calculateP(int *,int,SetInt,SetInt);
double calculateW(int *,SetInt,int,int);
void printOrderedList(Set,SetInt);

int main(int argc, char **argv)
{
    FILE *fp1;
    char url[BUFSIZE];
    int position[MAXURL][argc-1];
    
    int i, k;
    
    for (i = 0; i < MAXURL; i++)
    {
        for (k = 0; k < argc-1; k++)
            position[i][k] = 0;
    }
    
    SetInt listsize = newSetInt();
    SetInt p = newSetInt();
    Set unionlist = newSet();
    
    for (i = 1; i < argc; i++) // create union of two lists and store list size and url positions
    {
        fp1 = fopen(argv[i], "r");
        assert(fp1 != NULL);
        int j = 0;
        
        while (fscanf(fp1, "%s", url) != EOF)
        {
            j++;
            if (!isElem(unionlist,url))
            {
                insertInto(unionlist,url);
                printf( "Insert %s\n", url);
                printf( "New node is element no. %d\n", findNode(unionlist,url));
            }
            k = findNode(unionlist,url);
            if (k != -1)
            {
                position[k][i-1] = j;
                printf( "Position of %s in txt no. %d is %d\n", url, i, j);
            }
        }
        insertIntoInt(listsize,j);
        printf( "Size of txt no. %d is %d\n", i, j);
        fclose(fp1);
    }
    
    double w = 0;
    for (i = 0; i < nElems(unionlist); i++)
    {
        printf( "Calculate P of " );
        showNode(unionlist,i);
        insertIntoInt(p,calculateP(position[i], nElems(unionlist), listsize,p));
        w += calculateW(position[i], listsize, getValueInt(p,i), nElems(unionlist));
    }
    
    printf( "%.6f\n", w);
    printOrderedList(unionlist,p);
    
    disposeSet(unionlist);
    disposeSetInt(listsize);
    disposeSetInt(p);
}

void printOrderedList(Set unionlist, SetInt p)
{
    int i;
    
    for (i = 1; i <= nElemsInt(p); i++)
        showNode(unionlist,findNodeInt(p,i));
}

// getW(Set)
double calculateW(int * position, SetInt listsize, int p, int n)
{
    double a, b;
    double sum = 0;
    int i;

    printf( "Calculate W\n" );

    for (i = 0; i < nElemsInt(listsize); i++)
    {
        if (p != 0 && position[i] != 0)
        {
            a = (double)position[i]/(double)getValueInt(listsize,i);
            b = (double)p/(double)n;
            sum += fabs(a-b);
            printf( "a = %0.3f, b = %0.3f, c = %0.3f, sum = %0.3f\n", a, b, fabs(a-b), sum);
        }
        else
            printf( "Did not calculate w\n" );
    }
    return sum;
}

int calculateP(int * position, int n, SetInt listsize, SetInt plist)
{   
    double x[MAXURL];
    double min = 1;
    int i, p = -1;
    
    for (i = 0; i < nElemsInt(listsize); i++)
    {
        if (position[i] != 0)
        {
            x[i] = (double)(position[i]*n)/(double)getValueInt(listsize,i);
            printf( "x[%d] = %0.3f\n", i, x[i]);
            printf( "compare: %0.3f and %0.3f\n", fabs(round(x[i])-x[i]), min);
            if (!isElemInt(plist,round(x[i])))
            {
                if (fabs(round(x[i])-x[i]) < min)
                {
                    printf( "%0.3f better\n", x[i]);
                    min = fabs(round(x[i])-x[i]);
                    p = round(x[i]);
                }
                else
                    printf( "%0.3f not better\n", x[i]);
            }
            else
                printf( "%0.3f already in list\n", round(x[i]));
        }
        else
            printf( "Did not calculate p\n");
    }
    
    if (p = -1)
    
    printf( "p = %d\n", p);
    return p;
}
