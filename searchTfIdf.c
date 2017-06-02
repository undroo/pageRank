//Search TdIdf and calculations

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "set.h"
#include "ReadData.h"

#define BUFFSIZE 1024
#define OUTSIZE 10
#define OVERSIZE 100

Set isContain(Set);
Set findDuplicate(Set);
int assure(Set,Set);
void printSearch(Set, Set, int);


int main(int argc, char **argv){

	//check how many terms there are
	int numD = argc - 1;
	if (numD == 0){
		return 0;
	}
	Set collection = GetCollection();
	int count;
	Set terms = newSet();
	
	for (count = 0; count < numD; count++)
		insertInto(terms, argv[count+1]);

	
	Set tSet = newSet();
	tSet = isContain(terms);

	Set match = newSet();
	match = findDuplicate(tSet);
	
	printSearch(match, terms, nElems(collection));
	
	disposeSet(terms);
	disposeSet(tSet);
	disposeSet(match);
	disposeSet(collection);
	return 0;
}

int assure(Set a, Set b){
	if(nElems(a) != nElems(b)){
		return 1;
	}
	return 0;
}



Set isContain(Set terms){
	char string[BUFFSIZE];
	char word[BUFFSIZE];
	char *urls;
	int count;
	int num = nElems(terms);
	FILE *fp;
	fp = fopen("invertedIndex.txt", "r");
	
	Set list = newSet();
	
	while(fgets(string, BUFFSIZE, fp) != NULL){
		sscanf(string, "%s", word);
		for(count = 0; count < num; count++){
			if(strcmp(word, getValue(terms, count)) == 0){
				insertInto(list, string);
			}
		}
	}
	fclose(fp);
	return list;
}
	
Set findDuplicate(Set list){
	Set duplicate = newSet();
	Set loop = newSet();
	Set comparisons = newSet();
	int count;
	int countA;
	int dup = 0;
	int length;
	const char space[2] = " ";
	char *word;
	char *test;
	char *cut;
	char buff[BUFFSIZE];
	
	
	//create first set to compare urls
	test = strtok(getValue(list, 0), space);
	while (test != NULL){
		test = strtok(NULL, space);
		if (test == NULL) break;
			sscanf(test, "%s", test);
			insertInto(loop, test);
	}

	//if only searching one word, nothing to compare
	if (nElems(list) == 1){
		return loop;
	}
	
	//create second set to compare urls
	countA = 0;
	while (countA < nElems(list)){
			word = strtok(getValue(list, countA), space);
			while (word != NULL){
				word = strtok(NULL, space);
				if (word == NULL) break;
				sscanf(word, "%s", word);
				insertInto(comparisons, word);
			}
			countA++;
	}
	
	//comparing urls to find common ones
	count = 0;
	while (count < nElems(loop)){
		test = getValue(loop, count);
		dup = 1;
		countA = 0;
		while (countA < nElems(comparisons)){
			word = getValue(comparisons, countA);
			if(strcmp(word,test) == 0){
				dup++;
				if (dup == nElems(list)){
					if (nElems(duplicate) < nElems(loop) && nElems(duplicate) < nElems(comparisons))
						insertInto(duplicate, word);
				}
			}
			countA++;
		}
		count++;
	}
	disposeSet(loop);
	disposeSet(comparisons);
	return duplicate;	
}	
	

void printSearch(Set urlList, Set terms, int totalN){
	int count;
	int countA;
	int duplicate[nElems(terms)];
	memset(duplicate, 0, sizeof(nElems(terms)));
	char *url;
	char urlName[BUFFSIZE];
	char word[BUFFSIZE];
	char line[BUFFSIZE];
	FILE *fp;
	
	
	//showSet(urlList);
	for (count = 0; count < nElems(urlList); count++){
		url = getValue(urlList, count);
		sprintf(urlName, "%s.txt", url);
		fp = fopen(urlName, "r");
		if (fp == NULL) break;
		
		
		//get to section 2 in each text and each word
		while (strstr(fgets(line, BUFFSIZE, fp), "Section-2") == NULL) { }

		countA = 0;
		while(fscanf(fp, "%s", word) != EOF && strcmp(word,"#end") != 0){
			countA = 0;
			while(countA < nElems(terms)){
				//printf("%s\n", word);
				if (strcmp(word, getValue(terms, countA)) == 0){
					//printf("copy found: %s %s\n", word, urlName);
					duplicate[count]++;
				}
				countA++;
			}
		}
		fclose(fp);
	}
	
	
	double log10(double x);
	double value;
	double idf, doc;
	double tdidf[nElems(terms)];
	double rank[nElems(terms)];
	
	
	//finding tdidf values
	count = 0;
	while (count < nElems(urlList)){
		doc = (float)totalN/(float)nElems(urlList);
		idf = log10(doc);
		value = (float)duplicate[count] * idf;
		tdidf[count] = value;
		count++;
	}
	
	
	//sorting tdidf values in order
	//rather than sort array into correct order, obtain order in which results 
	//should be displayed
	int order[nElems(terms)];
	int position;
	count = 0;
	countA = 0;
	double max;
	memcpy(rank, tdidf, sizeof(rank));
	while (count < nElems(terms)){
		max = rank[count];
		countA = 0;
		position = 0;
		while (countA < nElems(terms)){
			if(max < rank[countA]){
				max = rank[countA];
				position = countA;
			}
			countA++;
		}
		rank[position] = 0;
		order[count] = position;
		count++;
	}
	
	//Printing final results
	for (count = 0; count < nElems(terms) && count < OUTSIZE; count++){
		printf("%s %.6f\n", getValue(urlList, order[count]), tdidf[order[count]]); 
	}
}
