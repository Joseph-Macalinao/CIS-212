/*
 * I believe I have completed:
 *  Map based on linked lists: yes/no
 *  Double hashing: yes/no
 *  Performance study: yes/no 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>





typedef struct
{
    char    *symbol;
    char    *name;
    float    lastSale;
    float    marketCap;
    int      IPOyear;
} Company;



typedef struct LinkedList{
	struct LinkedList *next;
	Company *companies;
	char *symb;	
} LinkedList;





void PrintCompany(Company *c)
{
    printf("%s:\n", c->name);
    printf("\tSymbol: %s\n", c->symbol);
    /* .2f: only print two digits after the period. */
    printf("\tLast Sale: %.2f\n", c->lastSale);
    printf("\tMarket Capitalization: %.2f\n", c->marketCap);
    printf("\tYear of Initial Public Offering: %d\n", c->IPOyear);
}

void ReadFile(const char *filename, Company **companies_rv, int *numCompanies_rv)
{
    int  i, j;

    if (filename == NULL)
    {
        fprintf(stderr, "No filename specified!\n");
        exit(EXIT_FAILURE);
    }
    FILE *f_in = fopen(filename, "r");
    if (f_in == NULL)
    {
        fprintf(stderr, "Unable to open file \"%s\"\n", filename);
        exit(EXIT_FAILURE);
    }

    fseek(f_in, 0, SEEK_END);
    int numChars = ftell(f_in);
    // printf("The number of characters is %d\n", numChars);
    fseek(f_in, 0, SEEK_SET);

    char *file_contents = malloc(sizeof(char)*numChars+1);
    fread(file_contents, sizeof(char), numChars, f_in);
    file_contents[numChars] = '\0';
    fclose(f_in);
    /* Note: the memory for this array is used to populate
     * the fields of the companies.  If it is freed, then
     * the company structs all become invalid.  For the
     * context of this program, this array should not be 
     * freed. */

    // Find out how many lines there are
    int numLines = 0;
    for (i = 0 ; i < numChars ; i++)
        if (file_contents[i] == '\n')
            numLines++;
    // printf("Number of lines is %d\n", numLines);

    int      numCompanies = numLines-1; // first line is header info 
    Company *companies    = malloc(sizeof(Company)*numCompanies);

    /* strtok will parse the file_contents array.  
     * The first time we call it, it will replace every '"' with '\0'.
     * It will also return the first word before a 
     */
    int numColumns = 9;
    int numberOfQuotesPerColumn = 2;
    strtok(file_contents, "\"");
    for (i = 0 ; i < numberOfQuotesPerColumn*numColumns-1 ; i++)
         strtok(NULL, "\"");
    for (i = 0 ; i < numCompanies ; i++)
    {
         companies[i].symbol = strtok(NULL, "\"");
         strtok(NULL, "\"");
         companies[i].name = strtok(NULL, "\"");
         strtok(NULL, "\"");
         companies[i].lastSale = atof(strtok(NULL, "\""));
         strtok(NULL, "\"");
         companies[i].marketCap = atof(strtok(NULL, "\""));
         strtok(NULL, "\""); 

         /* Skip ADR TSO */
         strtok(NULL, "\"");
         strtok(NULL, "\"");

         companies[i].IPOyear = atoi(strtok(NULL, "\""));
         strtok(NULL, "\"");

         /* Skip Sector, Industry, Summary Quote */
         for (j = 0 ; j < 6 ; j++)
             strtok(NULL, "\"");

         //PrintCompany(companies+i);
    }

    /* Set parameters to have output values */
    *companies_rv    = companies;
    *numCompanies_rv = numCompanies;
}

int hash(char *name, long array_size)
{
    int hashval = 0;
    char *p = name;
    while (*p != '\0')
    {
        hashval = 31*hashval + *p;
        p++;
    }

    return hashval%array_size;
}


int doubleHash(char *name, long array_size){
	int hashval = 0, i;
	for(i = 0; name[i] != '\0'; i++){
		hashval += (int) name[i];
	}
	return hashval % array_size;
}




typedef struct 
{
    int         numElements;
    char      **keys;
    Company    *companies;
} MapBasedOnHashTable;

void InitializeMapBasedOnHashTable(MapBasedOnHashTable *map, int numElements)
{
    map->numElements = numElements;
    map->keys = malloc(sizeof(char *)*numElements);
    map->companies = malloc(sizeof(Company)*numElements);
    for (int i = 0 ; i < numElements ; i++)
        map->keys[i] = NULL;
}

void StoreTo_MapBasedOnHashTable(MapBasedOnHashTable *map, Company *c)
{
    int hashval = hash(c->symbol, map->numElements);
    int doubleH = doubleHash(c->symbol, map->numElements);
    for (int i = 0 ; i < map->numElements ; i++)
    {
        int idx = (hashval +(i*doubleH))%(map->numElements);
        if (idx < 0) idx+= map->numElements;
        if (map->keys[idx] == NULL)
        {
            map->keys[idx]      = c->symbol;
            map->companies[idx] = *c;
            return;
        }
	}
    
}

LinkedList *StoreTo_LinkedList(Company *c, LinkedList *cur_head, LinkedList *nextN){
	//if(cur_head == NULL){
	//printf("yome");
	//LinkedList *nextN = (LinkedList*)malloc(sizeof(LinkedList));
	nextN->companies = c;
	nextN->symb = c->symbol;
	nextN->next = cur_head;
	return nextN;
	//}
	//cur_head->next = newNode;
	//if(cur_head != NULL){
	//	cur_head->prev = newNode;
	//}
	//newNode->prev = NULL;
	//printf("%s", (char *) newNode->val);
	
	/*else{
	LinkedList newNode = cur_head;
	while(newNode->next != NULL){
		newNode = newNode->next;
	}
	current->next = malloc(sizeof(LinkedList));
	current->next->companies = c;
	current->next->next = NUll
	}*/
	//return newNode;
}

Company *
FetchFrom_MapBasedOnHashTable(MapBasedOnHashTable *map, char *key)
{
    int hashval = hash(key, map->numElements);
    int doubleH = doubleHash(key, map->numElements);
    for (int i = 0 ; i < map->numElements ; i++)
    {
        int idx = (hashval+(i * doubleH))%(map->numElements);
        if (idx < 0) idx+= map->numElements;
        if (map->keys[idx] == NULL)
        {
            return NULL;
        }

        if (strcmp(map->keys[idx], key) == 0)
        {
            return &(map->companies[idx]);
        }
    }
    
    return NULL;
}



//Company *FetchdLinkedList(dLinkedList *dll, char *key){
Company *FetchdLinkedList(LinkedList *ll, char *key){
	if(ll == NULL){
		//printf("yo");
		return NULL;	
	}
	if(strcmp(ll->companies->symbol, key) == 0){
		//dLinkedList *rv = dll->next;
		//return &(*(rv->val));
		return ll->next->companies;
	}
	/*if((char *) dll->val == key){
		return &(*(dll->val));
	}
	FetchdLinkedList(dll->prev, key);*/
	LinkedList *prev = ll;
	LinkedList *cur = ll->next;
	while(cur != NULL){
		if(strcmp(cur->companies->symbol, key) == 0){
			//prev->next = cur->next;
			return ll->companies;
			}
			prev = cur;
			cur = cur->next;
	}
	return ll->companies;	
	//return NULL;
}





void FetchAndPrint(MapBasedOnHashTable *mfht, char *key)
{
    Company *c = FetchFrom_MapBasedOnHashTable(mfht, key);

    if (c == NULL)
    {
        printf("Key %s has no corresponding company\n", key);
    }
    else
    {
        PrintCompany(c);
    }

}

void FetchAndPrintDLL(LinkedList *dll, char *key){
	Company *c = FetchdLinkedList(dll, key);

	if (c == NULL){
		printf("Key %s has no corresponding company\n", key);
	}
	else{
		PrintCompany(c);
	}
}

int main(int argc, char *argv[])
        //dLinkedList cur_head = StoreTo_LinkedList(companies+i, &cur_head);
{
    Company *companies = NULL;
    int      numCompanies;
    ReadFile(argv[1], &companies, &numCompanies);
    MapBasedOnHashTable mfht;
    printf("num companies is %d\n", numCompanies);
    InitializeMapBasedOnHashTable(&mfht, numCompanies*2);
    
    struct timeval startTime;
    gettimeofday(&startTime, 0);
    for (int i = 0 ; i < numCompanies ; i++)
    {
        StoreTo_MapBasedOnHashTable(&mfht, companies+i);
    }
    struct timeval endTime;
    gettimeofday(&endTime, 0);
    double alloc_map = (double)(endTime.tv_sec - startTime.tv_sec) + (double)(endTime.tv_usec - startTime.tv_usec)/1000000;
    printf("It took %g time to allocate via mapping\n", alloc_map);
	
    
    
    struct timeval startTime3;
    gettimeofday(&startTime3, 0);
    FetchAndPrint(&mfht, "ZNWAA");
    FetchAndPrint(&mfht, "Z");
    FetchAndPrint(&mfht, "ZIOP");
    FetchAndPrint(&mfht, "ZIOQ");
    FetchAndPrint(&mfht, "YIOQ");
    FetchAndPrint(&mfht, "QIOQ");
    FetchAndPrint(&mfht, "WIOQ");
    FetchAndPrint(&mfht, "XIOQ");
    FetchAndPrint(&mfht, "TIOQ");
    FetchAndPrint(&mfht, "UIOQ");
    FetchAndPrint(&mfht, "VIOQ");
    struct timeval endTime3;
    gettimeofday(&endTime3, 0);
    double find_map = (double)(endTime3.tv_sec - startTime3.tv_sec) + (double)(endTime3.tv_usec - startTime3.tv_usec)/1000000;
    printf("It took %g time to find via mapping\n", find_map);
    
    
    int i = 0;
    //InitializeMapBasedOnHashTable(&mfht, numCompanies*2);
    //DLL *cur_head = NULL;
    LinkedList *cur_head = NULL;
	LinkedList *headNode, *currentNode, *temp;
    struct timeval startTime2;
    gettimeofday(&startTime2, 0);
    for (i = 0 ; i < numCompanies ; i++)
    {
        //dLinkedList cur_head = StoreTo_LinkedList(companies+i, &cur_head);
    	//LinkedList *newNode;
	//LinkedList *headNode, *currentNode, *temp;
	//LinkedList *cur_head = StoreTo_LinkedList(&(companies[i]), cur_head);//, newNode);
	//printf("%s\n", (char *) cur_head->companies->symbol);
	//LinkedList *cur_head = cur;
        //dLinkedList cur_head = StoreTo_LinkedList(companies+i, &cur_head);
	//LinkedList *cur_head = cur;
    	//printf("%d\n", i);
	//printf("%p\n, %s, %s\n", &cur_head, (char *)cur_head->companies->symbol, cur_head->next->companies->symbol);
	//
	//
	//currentNode = (LinkedList *)malloc(sizeof(LinkedList));

	//if(i == 0){
	//	headNode = temp = currentNode;
	//}
	//else{
		//StoreTo_LinkedList(companies+i, temp);
	//}
    
    
    LinkedList *newNode = (LinkedList *)malloc(sizeof(LinkedList));
    LinkedList *cur_head = StoreTo_LinkedList(&(companies[i]), cur_head, newNode);
    
    
    
    
    
    
    
    }
    //temp->next = NULL;
    //temp = headNode;
    //printf("%d\n", i);
    //printf("%s\n", (char *) cur_head->companies->symbol);
    //printf("%s\n", (char *)cur_head);

    struct timeval endTime2;
    gettimeofday(&endTime2, 0);
    double alloc_ll = (double)(endTime2.tv_sec - startTime2.tv_sec) + (double)(endTime2.tv_usec - startTime2.tv_usec)/1000000;
    printf("It took %g time to allocate via linked list\n", alloc_ll);
    
    /*for (int i = 0 ; i < numCompanies ; i++)
    {
        //dLinkedList cur_head = StoreTo_LinkedList(companies+i, &cur_head);
    	LinkedList *cur = StoreTo_LinkedList(companies+i, cur);
	//LinkedList *cur_head = cur;
        //dLinkedList cur_head = StoreTo_LinkedList(companies+i, &cur_head);
	//LinkedList *cur_head = cur;
    }*/
    

    
    struct timeval startTime4;
    gettimeofday(&startTime4, 0);
    FetchAndPrintDLL(cur_head, "ZNWAA");
    FetchAndPrintDLL(cur_head, "Z");
    FetchAndPrintDLL(cur_head, "ZIOP");
    FetchAndPrintDLL(cur_head, "ZIOQ");
    FetchAndPrintDLL(cur_head, "YIOQ");
    FetchAndPrintDLL(cur_head, "QIOQ");
    FetchAndPrintDLL(cur_head, "WIOQ");
    FetchAndPrintDLL(cur_head, "XIOQ");
    FetchAndPrintDLL(cur_head, "TIOQ");
    FetchAndPrintDLL(cur_head, "UIOQ");
    FetchAndPrintDLL(cur_head, "VIOQ");
    struct timeval endTime4;
    gettimeofday(&endTime4, 0);
    double find_ll = (double)(endTime4.tv_sec - startTime4.tv_sec) + (double)(endTime4.tv_usec - startTime4.tv_usec)/1000000;
    printf("It took %g time to find via linked list\n", find_ll);
}
/* YOUR PERFORMANCE STUDY WRITEUP GOES HERE:
 If this doesn't get done, I assume that LinkedLists would be much quicker at allocating space and creating nodes since they only
 need the address of the previous node, while the map needs to do math, go to the memory location, check if its NULL, and if not,
 go to a second address. However, I would guess that LinkedLists are actually SLOWER when it comes to going and gettting said 
 elements because it could possible go through the entire listing going from Node to Node seeing if the val matches what is wanted. 
 
 */
