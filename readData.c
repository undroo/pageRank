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
	char url[BUFFSIZE];
	AdjList M = newAdjList();
	
	
	
	int count = 0;
	while (count < nElems(urlSet)){
		strcpy(url, getValue(urlSet, count));
		FILE *fp;
		fp = fopen(strcat(url,".txt"), "r");
		
		if (strstr(fgets(line, BUFFSIZE, fp), "Section-1") != NULL);
		while (fscanf(fp, "%s", urlBuffer) != EOF){
			//check its inserting correctly
			//watch out for duplicates and self inclusion
			insertAdjListURL(M, url, urlBuffer);		
		}
		
		count++;
	}
	
	
	return M;
}



