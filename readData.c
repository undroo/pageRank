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


#define BUFSIZE 1024


Set GetCollection(){
	FILE *fp;
	fp = fopen("collection.txt", "r");
	char urlBuffer[BUFSIZE];
	
	Set urlSet = newSet();
	
	while (fscanf(fp, "%s", urlBuffer) != EOF)
		insertInto(urlSet, urlBuffer);
	
	fclose(fp);
	return urlSet;
}

AdjList buildM(Set urlSet){
	char line[BUFSIZE];
	char url[BUFSIZE];
	char fullurl[BUFSIZE];
	char urlBuffer[BUFSIZE];
	AdjList M = newAdjList();
	
	int count; 
	for (count = 0; count < nElems(urlSet); count++)
		insertAdjListNode(M, getValue(urlSet, count));
	
	for (count = 0; count < nElems(urlSet); count++)
	{
		strcpy(url,getValue(urlSet,count));
		strcpy(fullurl,url);
		
		FILE *fp;
		fp = fopen(strcat(fullurl,".txt"), "r");
		if (fp == NULL) break;
		
		while (strstr(fgets(line, BUFSIZE, fp), "Section-1") == NULL);
		while (fscanf(fp, "%s", urlBuffer) != EOF)
			insertAdjListURL(M, urlBuffer, url);	
	    
	    fclose(fp);	
	}	
	return M;
}


SetInt buildL(Set s)
{
    FILE * fp;
    char url[BUFSIZE];
    char word[BUFSIZE];
    char line[BUFSIZE];
    SetInt L = newSetInt();
    
    int i, n;
    for (i = 0; i < nElems(s); i++)
    {
        n = 0;
        strcpy(url, getValue(s,i));
        fp = fopen(strcat(url,".txt"), "r");
		while (strstr(fgets(line, BUFSIZE, fp), "Section-1") == NULL) { }
		while (fscanf(fp, "%s", word) != EOF )
        {
            if (strstr(word, "#end") != NULL) break;
            n++;
        }
        insertIntoInt(L,n);
        fclose(fp);
    }
    return L;
}
