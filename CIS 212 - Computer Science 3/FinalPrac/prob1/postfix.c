#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ADTs/stack.h"
#include <stdbool.h>

void createStack(const Stack *s, FILE *fp){
	long lcnt, i;
	char buf[BUFSIZ];
	fscanf(fp, "%ld", &lcnt); // Sets the number of lines in the file to lcnt
	for(i = 0; i <= lcnt; i++){
		fgets(buf, BUFSIZ, fp);
		char cmd[6] = "";
		long data = 0L;
		sscanf(buf, "%s %ld", cmd, &data);
		
		if(strstr(cmd, "+")){

		}
		if(strstr(cmd, "-")){

		}
		if(strstr(cmd, "*")){

		}
		if(strstr(cmd, "/")){

		}
	}
}

int main(int argc, char *argv[]){
	const Stack *s = Stack_create(free);
	FILE *fp;
	int exitStatus = EXIT_FAILURE;

	if(s == NULL){
		fprintf(stderr, "Unable to create stack");
		goto cleanup;
	}

	if(fp = fopen(argv[1], "r") == NULL){
		fprintf(stderr, "Unable to open file %s\n", fp);
		goto cleanup;
	}

	if(argc != 2){
		fprintf(stderr, "Incorrect usage, only one file and no flags allowed.");
		goto cleanup;
	}

	createStack(s, fp);
	exitStatus = EXIT_SUCCESS;

	cleanup:
		s->destroy(s);
		fclose(fp);
		return exitStatus;
}