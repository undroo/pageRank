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
    
    for (i = 0; i < MAXURL; i++) // initialise the 2D position array so each term is 0
    {
        for (k = 0; k < argc-1; k++)
            position[i][k] = 0;
    }
    
    // create sets to keep track of:
    SetInt listsize = newSetInt(); // size of input lists
    SetInt p = newSetInt(); // values of p
    Set unionlist = newSet(); // input urls
    
    for (i = 1; i < argc; i++) // open each input text file
    {
        fp1 = fopen(argv[i], "r");
        assert(fp1 != NULL);
        int j = 0;
        
        while (fscanf(fp1, "%s", url) != EOF) // scan through text file
        {
            j++; // keep track of position in text file
            if (!isElem(unionlist,url)) // insert url into set if not already existing
                insertInto(unionlist,url);
            k = findNode(unionlist,url); // find the index of the inserted/already existing url
            if (k != -1)
                position[k][i-1] = j; // update position array
        }
        insertIntoInt(listsize,j); // store final list size in set
        fclose(fp1);
    }
    
    double w = 0;
    for (i = 0; i < nElems(unionlist); i++) // calculate w by iterating through each url in set
    {
        insertIntoInt(p,calculateP(position[i], nElems(unionlist), listsize,p)); // calculate p using algorithm below, and insert into p set
        w += calculateW(position[i], listsize, getValueInt(p,i), nElems(unionlist)); // calculate individual term and increment w
    }
    
    printf( "%.6f\n", w);
    printOrderedList(unionlist,p);
    
    disposeSet(unionlist);
    disposeSetInt(listsize);
    disposeSetInt(p);
}

// printOrderedList(Set,SetInt)
// - takes the set of urls and set of p values and prints the urls in order of their positions
void printOrderedList(Set unionlist, SetInt p)
{
    int i;
    
    for (i = 1; i <= nElemsInt(p); i++)
        showNode(unionlist,findNodeInt(p,i));
}

// getW(Set)
// - calculate each individual term in w for each url in each list
double calculateW(int * position, SetInt listsize, int p, int n)
{
    double a, b;
    double sum = 0;
    int i;

    for (i = 0; i < nElemsInt(listsize); i++)
    {
        if (p != 0 && position[i] != 0)
        {
            a = (double)position[i]/(double)getValueInt(listsize,i);
            b = (double)p/(double)n;
            sum += fabs(a-b);
        }
    }
    return sum;
}

// calculateP(int *,int,SetInt,SetInt)
// This algorithm aims to minimise the value of w
// It finds the integer value of p that will make some terms in w become zero
// It calculates multiple values of p based on the url's position in the given lists
// It eliminates the non-integer solutions
// If no integer solutions are found, a value of p will be allocated that has not already been used
int calculateP(int * position, int n, SetInt listsize, SetInt plist)
{   
    double x[MAXURL];
    double min = 1;
    int i, p = -1;
    
    for (i = 0; i < nElemsInt(listsize); i++)
    {
        if (position[i] != 0)
        {
            x[i] = (double)(position[i]*n)/(double)getValueInt(listsize,i); // calculate the value of p for each list the url is in
            if (!isElemInt(plist,round(x[i]))) // check if the calculated value has already been allocated to another url
            {
                if (fabs(round(x[i])-x[i]) < min) // check if the calculate value is the closest so far to an integer
                {
                    min = fabs(round(x[i])-x[i]); // if so, update min for subsequent comparisons
                    p = round(x[i]); // allocated rounded value to p
                }

            }
        }
    }
    
    if (p == -1) // check if p has been allocated
        p = getInt(plist); // if not, generate int value that has not already been allocated
    
    return p;
}
