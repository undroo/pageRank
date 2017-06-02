//readData
//This function is heavily based on set.h and set.c from functions given in week 8 labs



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "readData.h"
#include "set.h"
#include "adjlist.h"


#define BUFFSIZE 255


Set GetCollection(){
	FILE *fp;
	fp = fopen("collection.txt", "r");
	char urlBuffer[BUFFSIZE];
	
	Set urlSet;
	urlSet = newSet();
	
	while (fscanf(fp, "%s", urlBuffer) != EOF){
		insertInto(urlSet, urlBuffer);
	}
	
	
	fclose(fp);
	return urlSet;
}

AdjList buildList(Set urlSet){
	char line[BUFFSIZE];
	char urlBuffer[BUFFSIZE];
	char *url;
	AdjList M = newAdjList();
	
	int count; 
	count = 0;
	while (count < nElems(urlSet)){
		insertAdjListNode(M, getValue(urlSet, count));
		count++;
	}
	
	count = 0;
	while (count < nElems(urlSet)){
		url = strcat(getValue(urlSet, count),".txt");
		FILE *fp;
		fp = fopen(url, "r");
		if (fp == NULL) break;
		while (strstr(fgets(line, BUFFSIZE, fp), "Section-1") == NULL);
		while (fscanf(fp, "%s", urlBuffer) != EOF){
			if (strcmp(urlBuffer, "#end") == 0) break;
			//remove .txt that was added from strcat
			strtok(getValue(urlSet, count),".txt");
			insertAdjListURL(M, urlBuffer, getValue(urlSet, count));		
		}
		count++;
	}	
	return M;
}



