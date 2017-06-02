//pagerank.c

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "set.h"
#include "adjlist.h"
#include "readData.h"


#define BUFSIZE 1024

float **pageRankArray(int, int, int, Set, AdjList);
float pageRank(int, int, int, char *, Set, AdjList);
float calcDiffPR(char *url, AdjList M);


int main(int argc, char **argv){

	if (argc != 4) return EXIT_FAILURE;
	
	
	double d = atof(argv[1]);
	double diffPR = atof(argv[2]);
	int maxIter = atoi(argv[3]);
	
	Set urlSet;
	urlSet = GetCollection();
	AdjList M;
	M = buildList(urlSet);
	
	showSet(urlSet);
	showAdjList(stdout, M);
	
	int N = nElems(urlSet);
	
	double PR[N][maxIter];
	
	int i, j;
	
    int iteration = 0;
	double diff = (double)diffPR;
    double a = (double)(1-d)/(double)N;
    
    char url[BUFSIZE];
    int index;
    
	for (i = 0; i < N; i++)
	    PR[i][0] = 1/(double)N;
	    
	while (iteration < maxIter && diff >= diffPR)
	{
	    iteration++;
	    
	    for (i = 0; i < N; i++) // iterate through url list
        {
	        Set m = getSet(M,i); // get M list of current url
	        
	        double sum = 0;
	        for (j = 0; j < nElems(m); j++) // iterate through M list
	        {
	            strcpy(url,getValue(m,j)); // get j'th url of M list
	            index = findAdjListNode(M,url); // get index of url
	            sum += (double)PR[index][iteration-1]/(double)nElems(getSet(M,j));
	        }
	        
	        PR[i][iteration] = (double)a + (double)d*(double)sum;
	    
	        diff = 0;
	        for (j = 0; j < N; j++)
	            diff += fabs(PR[i][iteration]-PR[i][iteration-1]);
	    }
	}
	
	for (i = 0; i < N; i++)
	    printf( "[%d]: %f\n", i, PR[i][iteration]);
	
	
	disposeSet(urlSet);
	disposeAdjList(M);
	
	return 0;
}
