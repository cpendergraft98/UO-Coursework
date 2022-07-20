#include "ADTs/stack.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

void printStack(const Stack *st, FILE *fp){
	
	char buf[BUFSIZ];
	while(fgets(buf, sizeof buf, fp) != NULL){
		int z = buf[1];

		if(z == 114){
			if(!(st -> isEmpty(st))){
				//int i;
				//int size = st -> size(st);
				//for(i = 0; i <= size; i++){
					//st -> pop(st, (void **)(long)&z);
					//printf("%d ", z);
				//}
				//printf("\n");
			}else{
				printf("Empty\n");
			}
		}

		if(z == 111){
			if(!(st -> isEmpty(st))){
				st -> pop(st, (void **)(long)&z);
				printf("%d\n", z);
			}else{
				printf("StackError\n");
			}
		}
			
		if(z == 117){
			long c = atoi(&buf[4]);
			(void)st -> push(st, (void *)(long)c);
		}
	}
}

int main(int argc, char *argv[]){
	FILE * fp = NULL;
	const Stack * st = Stack_create(free);
	int exitStatus = EXIT_FAILURE;

	if(argc != 2){
		fprintf(stderr, "usage: %s file\n", argv[0] );
		goto cleanup;
	}

	if((fp = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "cannot open file %s\n", argv[0] );
		goto cleanup;
	}

	if(st == NULL){
		fprintf(stderr, "%s: cannot create stack ADT instance\n", argv[0]);
		goto cleanup;
	}

	printStack(st, fp);
	exitStatus = EXIT_SUCCESS;

cleanup:
	if(st != NULL)
		st->destroy(st);
	if(fp != NULL)
		fclose(fp);
	return exitStatus;
}