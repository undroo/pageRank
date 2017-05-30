#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "set.h"
#include "adjlist.h"
#include "searchPagerank.h"

#define BUFSIZE 1024

int main(int argc, char **argv)
{
    FILE *fp1, *fp2;
    char url[BUFSIZE];
    Set inputs = newSet();
    Set results = newSet();
    
    int j = 1;
    for (j = 1; j < argc; j++)
    {
        if (!isElem(inputs,argv[j]))
            insertInto(inputs,argv[j]);
    }
    
    fp1 = fopen("pagerankList.txt", "r");
    assert(fp1 != NULL);
    
    int i = 0;
    while ((fscanf(fp1, "%s", url) != EOF) && i < 10)
    {
        if (strstr(normalise(url),"url"))
        {
            for (j = 0; j < nElems(inputs); j++)
            {
                fp2 = fopen("invertedIndex.txt", "r");
                assert(fp2 != NULL);
                if (!searchFile(fp2,getValue(inputs,j),url))
                    break;
                if (j == nElems(inputs) - 1)
                {
                    insertInto(results,url);
                    i++;
                }
                fclose(fp2);
            }
        }
    }
    fclose(fp1);
    
    for (j = 0; j < nElems(results); j++)
        puts(getValue(results,j));
    
}

// searchLine(FILE *,char *,char *)
// - search file for word and url
// - return 1 if word and url are on same line
// - else return 0
int searchFile(FILE *fp, char * word, char * url)
{
    char line[BUFSIZE];
    while (fgets(line,BUFSIZE,fp) != NULL)
    {
        if (strstr(line,word) != NULL && strstr(line,url) != NULL) // word & url are both in line
            return 1;
        else if (strstr(line,word) != NULL && strstr(line,url) == NULL)
            return 0;
    }
    return 0;
}

char *normalise(char *word)
{
    char *url;
    url = word;
    while (*url != '\0')
    {
        *url = tolower(*url);
        if (!((*url >= 'a' && *url <= 'z') || (*url >= '0' && *url <= '9') || *url == '-'))
        {
            *url = '\0';
            break;
        }
        url++;
    }

    return word;
}
