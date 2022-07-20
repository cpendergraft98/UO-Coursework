/*
balanceCheck - Checks a given expression to examine the pairs and the orders of '{', '}', '[', ']', '(', ')', '<', '>', are correct.

Author: Thomas Joyce
Usage: ./balanceCheck FILE
*/
#include "ADTs/stack.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

char matchSet(long cropen) {
	char *opbr = "([{<";
	char *clbr = ")]}>";
	char c = ' ';
	int len = strlen(opbr) -1;
	for(int it = 0; it <= len; it++) {
		if((char)cropen == opbr[it]) {
			c = clbr[it];
		}
	}
	return c;
}

void balanced(FILE *fp, const Stack *st){
	long lcnt, i;
	char opbr[] = "([{<";
    char buf[BUFSIZ];
	fgets(buf, BUFSIZ, fp);
	lcnt = atol(buf);
	for(i = 0; i <= lcnt - 1; i++) {
		bool isBalanced = false;
		st->clear(st);
		fgets(buf, BUFSIZ, fp);
		int stcnt = strlen(buf) - 1;
		int it;
		for(it = 0; it < stcnt; it++) {
			char c = buf[it];
			if(strchr(opbr, c)) {
				(void)st->push(st, (void *)(long)c);
			}else {
				long cropen;
				(void)st->pop(st, (void **)&cropen);
				if(c == matchSet(cropen)) {
					isBalanced = true;
					continue;
				} else {
					isBalanced = false;
					break;
				}
			}
		}
		if(isBalanced && st->isEmpty(st)) {
			fprintf(stdout, "YES\n");
		}else {
			fprintf(stdout, "NO\n");
		}
	}
}

int main(int argc, char *argv[]){
	FILE *fp = NULL;
	const Stack * st = Stack_create(NULL);
	int exitStatus = EXIT_FAILURE;
	if(argc != 2) {
		fprintf(stderr, "Incorrect usage. Usage: %s file\n", argv[0]);
		goto cleanup;
	}
	if((fp = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "Unable to open given file: %s\n", argv[1]);
		goto cleanup;
	}
	if(st == NULL) {
		fprintf(stderr, "Cannot create stackADT...\n");
		goto cleanup;
	}
	balanced(fp, st);
	exitStatus = EXIT_SUCCESS;


cleanup:
	if(st != NULL)
		st->destroy(st);
	if(fp != NULL)
		fclose(fp);
	return exitStatus;
}