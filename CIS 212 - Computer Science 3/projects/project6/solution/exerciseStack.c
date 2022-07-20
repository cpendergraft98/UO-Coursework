/*
exerciseStack - takes an input file containing instructions for stack operations.

Author: Thomas Joyce
Usage: ./exerciseStack FILE
*/
#include "ADTs/stack.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

void printStack(const Stack *st, FILE *fp) {
	long ltmp;
	const Stack *stmp = st->create(st);
	if(stmp == NULL) {
		fprintf(stderr, "Cannot create stackADT...\n");
		goto cleanup;
	}
	if(st->isEmpty(st)) {
		fprintf(fp, "Empty\n");
		goto cleanup;
	}else {
		while(!st->isEmpty(st)) {
			st->pop(st, (void *)&ltmp);
			fprintf(fp, "%ld%s", ltmp, (!st->isEmpty(st)) ? " " : "\n");
			stmp->push(stmp, (void *)(long) ltmp);
		}
		while(!stmp->isEmpty(stmp)) {
			stmp->pop(stmp, (void *)&ltmp);
			st->push(st, (void *)(long) ltmp);
		}
	}
cleanup:
	stmp->destroy(stmp);
}

void formStack(const Stack *st, FILE *fp) {
	long lcnt, it;
	char buf[BUFSIZ];
	fscanf(fp, "%ld", &lcnt);
	for(it = 0; it <= lcnt; it++) {
		fgets(buf, BUFSIZ, fp);
		char cmd[6] = "";
		long data = 0L;
		sscanf(buf, "%s %ld", cmd, &data);
		if(strstr(cmd, "push")) {
			st->push(st, (void *)(long)data);
			continue;
		}
		if(strstr(cmd, "pop")) {
			if(!st->pop(st, (void *)&data)) {
				fprintf(stdout, "StackError\n");
				continue;
			}
			fprintf(stdout, "%ld\n", data);
			continue;
		}
		if(strstr(cmd, "print")) {
			printStack(st, stdout);
			continue;
		}
	}
}

int main(int argc, char *argv[]) {
	FILE *fp = NULL;
	const Stack * st = Stack_create(NULL);
	if(st == NULL) {
		fprintf(stderr, "Cannot create stackADT...\n");
		goto cleanup;
	}
	int exitStatus = EXIT_FAILURE;
	if(argc != 2) {
		fprintf(stderr, "Incorrect usage. Usage: %s file\n", argv[0]);
		goto cleanup;
	}
	if((fp = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "Unable to open given file: %s\n", argv[1]);
		goto cleanup;
	}
	formStack(st, fp);
	exitStatus = EXIT_SUCCESS;

cleanup:
	if(st != NULL)
		st->destroy(st);
	if(fp != NULL)
		fclose(fp);
	return exitStatus;
}
