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
    
    fp1 = fopen("pagerankList.txt", "r");
    assert(fp1 != NULL);
    
    int i = 0, n = 1;
    while ((fscanf(fp1, "%s", url) != EOF) && i < 10)
    {
        if (strstr(normalise(url),"url"))
        {
            fp2 = fopen("invertedIndex.txt", "r");
            assert(fp2 != NULL);
 
            int j;
            for (j = 1; j < argc && n == 1; j++)
                n = searchLine(fp2,argv[j],url);
            
            if (n == 1)
            {
                puts( url );
                i++;
            }
            n = 1;
            fclose(fp2);
        }
    }
    fclose(fp1);
}

// searchLine(FILE *,char *,char *)
// - search file for word and url
// - return 1 if word and url are on same line
// - else return 0
int searchLine(FILE *fp, char * word, char * url)
{
    char line[BUFSIZE];
    while (fgets(line,BUFSIZE,fp) != NULL)
    {
        if (strstr(line,word) != NULL && strstr(line,url) != NULL) // word & url are both in line
            return 1;
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
