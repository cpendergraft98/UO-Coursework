#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llistprioqueue.h"
#include "prioqueue.h"

#define BUFSIZE 128

int cmp(void *a, void *b){
	//TODO
}

void freePrio(void *p){
	//TODO
}

void freeValue(void *v){
	//TODO
}

int main(int argc, char *argv[]){
	const PrioQueue *pq = NULL;
	const Iterator *it = NULL;
	char buffer[BUFSIZE];
	int status = EXIT_FAILURE;
	FILE *pFile = NULL;
	int *priority = NULL;
	char *word = NULL;
	long lineno = 0;
		
	//TODO

	if(argc != 2){
		fprintf(stderr, "Uage: %s fileName \n", argv[0]);
		goto cleanup;
	}

	pFile = fopen(argv[1], "r");

	if(pFile == NULL){
		fprintf(stderr, "Unable to open file: %s !\n", argv[1]);
		goto cleanup;
	}else{
		while(fgets(buffer, BUFSIZE, pFile) != NULL){
			//TODO
		}
		fclose(pFile);
	}

	it = pq->itCreate(pq);
	if(it != NULL){
		while(it->hasNext(it)) {
			//TODO
		}
		it->destroy(it);
	} else {
		fprintf(stderr, "Unable to create iterator over priority queue\n");
		goto cleanup;
	}

	//TODO

	status = EXIT_SUCCESS;

	cleanup:
	if(pq != NULL)
		pq->destroy(pq);
			
	return status;
}
