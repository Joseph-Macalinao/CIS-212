
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_SIZE 10

typedef struct{ 
	int num_elements;
	char *strings[QUEUE_SIZE];
	int front;
	int back;
	
} Queue;


void InitializeQueue(Queue *q){
	q->num_elements = 0;
	q->front = 0;
	q->back = 0;
}

void Enqueue(Queue *q, char *val){
	if (q->num_elements == QUEUE_SIZE){
		return;
	}
	else{
		if (q->back == 0){
		
			q->num_elements++;
			//q->back = q->back + 1;
			//if (q->back == QUEUE_SIZE){
			//	q->back = 0;
			//}
			q->strings[q->back] = val;
			q->back = q->back + 1;
			return;
		}
		q->num_elements++;
		//q->back = q->back + 1;
		if (q->back == QUEUE_SIZE){
			q->back = 0;
		}
		char *cop = malloc(sizeof(char) * strlen(val));
		//q->strings[q->back] = val;
		strcpy(cop, val);
		q->strings[q->back] = val;
		q->back = q->back + 1;
	}
}

char *Front(Queue *q){
	if(q->num_elements==0){
		return "No elements";
	}
	return q->strings[q->front];
}


char *Dequeue(Queue *q){
	printf("%p\n", &q);
	char *top;
	if (q->num_elements == 0){
		return "No more elements";
	}
	else{
		top = Front(q);
		//char *front = q->strings[q->front];
		q->num_elements--;
		q->front++;

		if(q->front == QUEUE_SIZE){
			q->front = 0;
		}
	}
	return top;
}








void
PrintQueue(Queue *q)
{
    int i;
    printf("Printing queue %p\n", q);
    printf("\tThe index for the front of the queue is %d\n", q->front);
    printf("\tThe index for the back of the queue is %d\n", q->back);
    if (q->front == q->back)
    //if (q->num_elements == 0)
    {
        printf("\tThe queue is empty.\n");
        return;
    }
    int back = q->back;
    if (q->back < q->front)
    {
        // wrapped around, so modify indexing 
        back += QUEUE_SIZE;
    }

    for (i = q->front ; i < back ; i++)
    {
        printf("\t\tEntry[%d] = \"%s\"\n", i%QUEUE_SIZE, q->strings[i%QUEUE_SIZE]);
    }
}
 


void
PrettyPrintQueue(Queue *q, char *type)
{
    if (Front(q) == NULL)
    {
        printf("No unmatched entries for %s\n", type);
    }
    else
    {
        char *s;
        printf("Unmatched %s:\n", type);
        while ((s = Dequeue(q)))
        {
            printf("%s\n", s);
        }
    }
}
 

char *NewString(char *s)
{
    int len = strlen(s);
    char *rv = malloc(len+1);
    strcpy(rv, s);
    rv[len-1] = '\0'; /* take out newline */
    return rv;
}



int main(int argc, char *argv[])
{
/***  STEP #1: Test your queue code.  ***/
/*
 //This code:
    Queue q;
    InitializeQueue(&q);
    PrintQueue(&q);
    Enqueue(&q, "hello");
    PrintQueue(&q);
    Enqueue(&q, "world");
    PrintQueue(&q);
    printf("Dequeue: %s\n", Dequeue(&q));
    PrintQueue(&q);
*/
/* Gives this output (with different pointers):
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 0
	The queue is empty.
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 1
		Entry[0] = "hello"
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 2
		Entry[0] = "hello"
		Entry[1] = "world"
Dequeue: hello
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 1
	The index for the back of the queue is 2
		Entry[1] = "world"
 */

/*** STEP #2: read in from the input file (argc/argv stuff). 
     NewString is likely helpful here.
 ***/
	Queue femDon;
	InitializeQueue(&femDon);
	//printf("%p\n", &femDon);
	Queue malDon;
	InitializeQueue(&malDon);
	//printf("%p\n", &malDon);
	Queue femRec;
	InitializeQueue(&femRec);
	//printf("%p\n", &femRec);
	Queue malRec;
	InitializeQueue(&malRec);
	//printf("%p\n", &malRec);
	Queue Hospital;
	InitializeQueue(&Hospital);
	//printf("%p\n", &Hospital);
	int buff_size;
    	char fLine[150];
	FILE *f_in = fopen(argv[1], "r");

    	//printf("%s", argv[1]);
	if (f_in == NULL){
    		exit(EXIT_FAILURE);
    	}

    	while(!feof(f_in)){
	//while(fgets(fLine, 150, f_in) != NULL){
		fgets(fLine, 150, f_in);
		char *strlin = NewString(fLine);
		//printf("%s", fLine);
		//fgets(fLine, 50, f_in);
		//printf("%s", fLine);
	 	//printf("%s\n", strlin);	
		if ((fLine[0] == 'D' && fLine[2] == 'F')){
			//printf("%s", fLine);
					
			Enqueue(&femDon,fLine);
			if (femRec.num_elements > 0 && Hospital.num_elements > 0){
			       char *hosp = Dequeue(&Hospital);
			       //printf("%s", hosp);
			       char *recip = Dequeue(&femRec);
			       //printf("%s", recip);
			       char *donor = Dequeue(&femDon);
    			       //printf("%s", donor);
			       printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
			
			}
		}
		if ((fLine[0] == 'D' && fLine[2] == 'M')){
			//printf("%s", fLine);
			
			Enqueue(&malDon,fLine);
			if (malRec.num_elements > 0 && Hospital.num_elements > 0){
				char *hosp = Dequeue(&Hospital);
			       //printf("%s", hosp);
				char *recip = Dequeue(&malRec);
			       //printf("%s", recip);
				char *donor = Dequeue(&malDon);
    			       //printf("%s", donor);
    				printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
			}	
		}
		if ((fLine[0] == 'R' && fLine[2] == 'F')){
			//printf("%s", fLine);
			
			Enqueue(&femRec,fLine);
			if (femDon.num_elements > 0 && Hospital.num_elements > 0){
				char *hosp = Dequeue(&Hospital);
			       //printf("%s", hosp);
				char *recip = Dequeue(&femRec);
			       //printf("%s", recip);
				char *donor = Dequeue(&femDon);
    			       //printf("%s", donor);
    				printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
			}
		}
		if ((fLine[0] == 'R' && fLine[2] == 'M')){
			//printf("%s", fLine);
			
			Enqueue(&malRec,fLine);
			if (femDon.num_elements > 0 && Hospital.num_elements > 0){
				char *hosp = Dequeue(&Hospital);
			       //printf("%s", hosp);
				char *recip = Dequeue(&malRec);
			       //printf("%s", recip);
				char *donor = Dequeue(&malDon);
    			       //printf("%s", donor);
    				printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
			}
		}
		if (fLine[0] == 'H'){
			//printf("%s", fLine);
			
			Enqueue(&Hospital,fLine);
			if ((femRec.num_elements > 0) && (femDon.num_elements > 0) || (malRec.num_elements > 0) && (malDon.num_elements > 0)){
				char *hosp = Dequeue(&Hospital);
			       //printf("%s", hosp);
				char *recip = Dequeue(&femRec);
			       //printf("%s", recip);
				char *donor = Dequeue(&femDon);
    			       //printf("%s", donor);
    				printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
			}
		}
		if (fLine == NULL){
			int x = 0;
		}
		    	}	

    

	fclose(f_in);
	}
    	
/*** STEP #3: *after* your queue code works and *after* you can read the file, 
     implement the prompt ***/
/* Here are some helpful lines of code:
 *
 *  My print statement for a match:
 *
    printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
 *
 *
 *  My print statements for the contents of the queues at the end:
 *
    PrettyPrintQueue(&female_donors, "female donors");
    PrettyPrintQueue(&female_recipients, "female recipients");
    PrettyPrintQueue(&male_donors, "male donors");
    PrettyPrintQueue(&male_recipients, "male recipients");
    PrettyPrintQueue(&hospitals, "hospitals");
 *
 */
	//}
	//
	//
	//


//int main(int argc, char *argv[])
//{
/***  STEP #1: Test your queue code.  ***/
/*
 //This code:
    Queue q;
    InitializeQueue(&q);
    PrintQueue(&q);
    Enqueue(&q, "hello");
    PrintQueue(&q);
    Enqueue(&q, "world");
    PrintQueue(&q);
    printf("Dequeue: %s\n", Dequeue(&q));
    PrintQueue(&q);
*/
/* Gives this output (with different pointers):
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 0
	The queue is empty.
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 1
		Entry[0] = "hello"
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 2
		Entry[0] = "hello"
		Entry[1] = "world"
Dequeue: hello
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 1
	The index for the back of the queue is 2
		Entry[1] = "world"
 */

/*** STEP #2: read in from the input file (argc/argv stuff). 
     NewString is likely helpful here.
 ***/
/*	Queue femDon;
	InitializeQueue(&femDon);
	Queue malDon;
	InitializeQueue(&malDon);
	Queue femRec;
	InitializeQueue(&femRec);
	Queue malRec;
	InitializeQueue(&malRec);
	Queue Hospital;
	InitializeQueue(&Hospital);
	int buff_size;
    	char fLine[150];
	FILE *f_in = fopen(argv[1], "r");

    	//printf("%s", argv[1]);
	if (f_in == NULL){
    		exit(EXIT_FAILURE);
    	}

    	//while(!feof(f_in)){
	while(fgets(fLine, 150, f_in) != NULL){
		fgets(fLine, 150, f_in);
		char *strlin = NewString(fLine);
		//fgets(fLine, 50, f_in);
		//printf("%s", fLine);
		
		if ((strlin[0] == 'D') && (strlin[2] == 'F')){
			//printf("%s", fLine);
					
			Enqueue(&femDon,fLine);
			if (femRec.num_elements > 0 && Hospital.num_elements > 0){
			       char *hosp = Dequeue(&Hospital);
			       char *recip = Dequeue(&femRec);
			       char *donor = Dequeue(&femDon);
    			       printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
			
			}
		}
		if ((strlin[0] == 'D') && (strlin[2] == 'M')){
			//printf("%s", fLine);
			
			Enqueue(&malDon,fLine);
			if (malRec.num_elements > 0 && Hospital.num_elements > 0){
				char *hosp = Dequeue(&Hospital);
				char *recip = Dequeue(&malRec);
				char *donor = Dequeue(&malDon);
    				printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
			}	
		}
		if ((strlin[0] == 'R') && (strlin[2] == 'F')){
			//printf("%s", fLine);
			
			Enqueue(&femRec,fLine);
			if (femDon.num_elements > 0 && Hospital.num_elements > 0){
				char *hosp = Dequeue(&Hospital);
				char *recip = Dequeue(&femRec);
				char *donor = Dequeue(&femDon);
    				printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
			}
		}
		if ((strlin[0] == 'R') && (strlin[2] == 'M')){
			//printf("%s", fLine);
			
			Enqueue(&malRec,fLine);
			if (femDon.num_elements > 0 && Hospital.num_elements > 0){
				char *hosp = Dequeue(&Hospital);
				char *recip = Dequeue(&malRec);
				char *donor = Dequeue(&malDon);
    				printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
			}
		}
		if (strlin[0] == 'H'){
			//printf("%s", fLine);
			
			Enqueue(&Hospital,fLine);
			if ((femRec.num_elements > 0) && (femDon.num_elements > 0)){
				char *hosp = Dequeue(&Hospital);
				char *recip = Dequeue(&femRec);
				char *donor = Dequeue(&femDon);
    				printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
			}
			if((malRec.num_elements > 0) && (malDon.num_elements > 0)){
				char *hosp = Dequeue(&Hospital);
				char *recip = Dequeue(&femRec);
				char *donor = Dequeue(&femDon);
    				printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
			}
		}
		    	}	

    

	fclose(f_in);
	}
 */   	
/*** STEP #3: *after* your queue code works and *after* you can read the file, 
     implement the prompt ***/
/* Here are some helpful lines of code:
 *
 *  My print statement for a match:
 *
    printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
 *
 *
 *  My print statements for the contents of the queues at the end:
 *
    PrettyPrintQueue(&female_donors, "female donors");
    PrettyPrintQueue(&female_recipients, "female recipients");
    PrettyPrintQueue(&male_donors, "male donors");
    PrettyPrintQueue(&male_recipients, "male recipients");
    PrettyPrintQueue(&hospitals, "hospitals");
 *
 */
