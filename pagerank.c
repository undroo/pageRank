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


#define BUFFSIZE 1024

float **pageRankArray(int, int, int, Set, AdjList);
float pageRank(int, int, int, char *, Set, AdjList);
float calcDiffPR(char *url, AdjList M);


int main(int argc, char **argv){

	
	Set urlSet;
	urlSet = GetCollection();
	
	AdjList M;
	M = buildList(urlSet);
	showAdjList(M);
	
	
	
	int d = atoi(argv[1]);
	int diffPR = atoi(argv[2]);
	int maxIter = atoi(argv[3]);
	int num = nElems(urlSet);
	float **PR;
	PR = pageRankArray(d, diffPR, maxIter, urlSet, M);
	
	disposeSet(urlSet);
	free(urlSet);
	
	
	
	/*
	Structure for pageRank
	open file collection.txt
	read all urls into a set, urlSet
	check for duplicates in set
	
	while (fscanf(fp, "%s", urlBuffer)){
		insertInto(urlSet, urlBuffer);
	}
	
	create adjacency list M with numUrl vertices
	Foreach 'cur' url in urlSet {
		add 'cur' into matrix
		
		function from readData(char 'cur', Graph g){
			use snprintf to create file name 'cur' url.txt
			fopen new .txt file
			add in all pointers that cur points to
			eg. cur -> url1, add cur to url1, since we are doing inverted index 
		}
			
		
		increment through
	}
	
	create pageRank array ()
		2d integer array
		how to save the order in which urls are created?
		each node in set will save url name as well as a number to signify the order
		
	
	calculate pageRank using adjacency list M()
	while (going across pageRank array){
		reset urls
		while(going down pageRank array){
			if ()
			function calculate pageRank();
			add value to pageRank array
			increment through urlSet
			increment 
		}
		increment
	}
	
	
	
	
	disposeGraph(M)
	*/
	
	
	
	
	return 0;
}


float **pageRankArray(int d, int diffPR, int maxIter, Set urlSet, AdjList M){
	
	int num = nElems(urlSet);
	int countA = 0;
	int countB = 0;
	float diff = diffPR;
	char *url;
	
	
	float **PR = (float **)malloc(sizeof(float *)*num);
	for (countA = 0; countA < num; countA++){
		PR[countA] = (float *)malloc(sizeof(float)*maxIter);
	}
	
	
	countA = 0;
	while(countA < maxIter && diff >= diffPR){
		countB = 0;
		while(countB < num){
			if (countA == 0){
				PR[countA][countB] = 1/num;
			} else {
				url = getValue(urlSet, countB);
				PR[countA][countB] = pageRank(d, diffPR, maxIter, url, urlSet, M);
				diff = calcDiffPR(url, M);
			}
			countB++;
		}
		countA++;
	}
	
	
	
	return PR;
}

float calcDiffPR(char *url, AdjList M){
	
	
	return 0;
}

float pageRank(int d, int diffPR, int maxIter, char *url, Set urlSet, AdjList M){
	
	
	return 0;
}

