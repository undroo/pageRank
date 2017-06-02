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
#include "setInt.h"


#define BUFSIZE 1024

int main(int argc, char **argv){

	if (argc != 4) return EXIT_FAILURE;
	
	double d = atof(argv[1]); // collect input numbers
	double diffPR = atof(argv[2]);
	int maxIter = atoi(argv[3]);
	
	Set urls = GetCollection(); // collect urls from collection.txt
	AdjList M = buildM(urls); // build adjacency list to keep track of which urls point where
	SetInt L = buildL(urls); // build list to keep track of urls' out degrees
	SetInt rank = newSetInt(); // create set to store ranking of urls
	
	int N = nElems(urls);
	double PR[N][maxIter]; // 2D matrix to store page ranks
	int i, j;  
    char url[BUFSIZE];
    int index;
    int iteration = 0;
	double diff = diffPR;
    
    // commence PageRank algorithm
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
	            sum += PR[index][iteration-1]/(double)getValueInt(L,index);
	        }
	        
	        PR[i][iteration] = (1-d)/N + d*sum; // calculate PageRank and store in array
	        
	        diff = 0; // calculate diff
	        for (j = 0; j < N; j++)
	            diff += fabs(PR[i][iteration]-PR[i][iteration-1]);
	    }
	}
	// end PageRank algorithm
	
	// commence ordering urls in descending order
	insertIntoInt(rank,0); // Rank list stores the url indices, when the urls are in descending order
    for (i = 1; i < N; i++)
    {
        for (j = i-1; j >= 0; j--) // Iterate through already inserted nodes until reaches a node of greater PR value
        {
            index = getValueInt(rank,j);
            double n = PR[i][iteration];
            double m = PR[index][iteration];
            if(n <= m)
            {
                insertAfterInt(rank,i,index);
                break;
            } 
        }
    }
    // end ordering
    
    for (i = 0; i < N; i++)
    {
        index = getValueInt(rank,i);
        printf( "%s, %d, %0.8f\n", getValue(urls,index), getValueInt(L, index), PR[index][iteration]);
    }
    
	disposeSet(urls);
	disposeAdjList(M);
	disposeSetInt(L);
	disposeSetInt(rank);
	
	return 0;
}
