#include <stdio.h>
#include <stdlib.h>
#define UNUSED __attribute__((unused))
#include "stsplit.h"

int main(UNUSED int argc, UNUSED char *argv[]) {
	long wcnt = 0L;
	char buf[BUFSIZ];
	char **words;
	int exitStatus = EXIT_SUCCESS;

	while (fgets(buf, sizeof buf, stdin) != NULL){
		words = stsplit(buf);
		for (int i = 0; words[i] != NULL; i++){
			wcnt++;
		}
		stfree(words);
	}
	printf("%8ld\n", wcnt);
	stfree(words);
	return exitStatus;
}
