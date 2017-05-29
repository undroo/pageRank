//readData
//This function is heavily based on set.h and set.c from functions given in week 8 labs



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/*
#include "readData.h"
#include "pagerank.c"
*/
#include "set.h"
#include "graph.h"

int main(int argc, char **argv)
{
	FILE *fp;
	fp = fopen(collection.txt, "r");
	char urlBuffer[BUFFSIZE];
	char wordBuffer[BUFFSIZE];
	
	
	Set *url;
	urlList = newSet();
	while (fscanf(fp, "%s", urlBuffer) != 0){
		insertInto(urlList, urlBuffer);
	}
	
	
	
	return 0;
}


Set GetCollection()
{
    FILE * fp = fopen( "collection.txt", "r" );
    char url[BUFSIZE];
    
    Set URLlist = newSet();

    while ( fscanf(fp, "%s", url) != EOF )
        insertInto(URLlist, url);
    
    return URLlist;
}
