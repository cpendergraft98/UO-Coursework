#include "ADTs/queue.h"
#include "ADTs/llistqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void printQueue(const Queue *q, FILE *fp){
	const Iterator *it = q -> itCreate(q);
	int n = 0;
	if(q -> isEmpty(q)){
		fprintf(fp, "Empty\n");
	}
	if(it == NULL)
		return;
	while(it -> hasNext(it)){
		long lvalue;
		(void)it -> next(it, (void **)&lvalue);
		printf("%s%ld", (n++ == 0) ? "" : " ", lvalue);
	}
	printf("\n");
	it -> destroy(it);
}

void createQueue(const Queue *q, FILE *fp){
	long lcnt, i;
	char buf[BUFSIZ];
	fscanf(fp, "%ld", &lcnt);
	for(i = 0; i <= lcnt; i++){
		fgets(buf, BUFSIZ, fp);
		char cmd[6] = "";
		long data = 0L;
		sscanf(buf, "%s %ld", cmd, &data);
		if(strstr(cmd, "enqueue")){
			q -> enqueue(q, (void *)(long)data);
			continue;
		}
		if(strstr(cmd, "dequeue")){
			if(!q -> dequeue(q, (void *)&data)){
				fprintf(stdout, "QueueError\n");
				continue;
			}
			fprintf(stdout, "%ld\n", data);
			continue;
		}
		if(strstr(cmd, "print")){
			printQueue(q, stdout);
			continue;
		}
	}
}

int main(int argc, char *argv[]){
	FILE *fp = NULL;
	const Queue *q = Queue_create(NULL);
	int exitStatus = EXIT_FAILURE;
	q = LListQueue(NULL);

	if(q == NULL){
		fprintf(stderr, "Cannot create Queue ADT....\n");
		goto cleanup;
	}

	if(argc != 2){
		fprintf(stderr, "Incorrect usage. Should be: %s file\n", argv[0]);
		goto cleanup;
	}

	if((fp = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "Unable to open file: %s\n", argv[1]);
		goto cleanup;
	}

	createQueue(q, fp);
	exitStatus = EXIT_SUCCESS;
	goto cleanup;

	cleanup:
		q -> destroy(q);
		fclose(fp);
		return exitStatus;
}