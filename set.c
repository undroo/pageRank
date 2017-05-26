//Set functions

typedef  struct Node *list;

typedef struct Node {
	char *urlName;
	list *next;
} Node;

typedef struct SetRep {
	int elems;	
	list first;
	list urlList;
} SetRep;

Set newSet();
void insertInto(Set, char *);


static Link newNode(char *);

Set newSet()
{
	Set new = malloc(sizeof(SetRep));
	assert(new != NULL);
	new->elems = 0;
	new->first = NULL;
	new->urlList = NULL;
	return new;
}

void insertInto(Set S, char *string)
{	
	assert(s != NULL);
	if (S->first != NULL){
		
	} else {
		list new = newNode
	}
	
}

//Helper Functions

static Link newNode(char *url)
{
	list new = malloc(sizeof(Node));
	assert(new != NULL);
	new->urlName = strdup(url);
	new->next = NULL;
	return new;
}
