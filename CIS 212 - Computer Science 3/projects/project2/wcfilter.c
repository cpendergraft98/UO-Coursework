#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stsplit.h"
#define UNUSED __attribute__((unused))

void countLWC(FILE *fd, long *nl, long *nw, long *nc) {
	char **words;
	char buf[BUFSIZ];

	while (fgets(buf, sizeof buf, fd) != NULL){
		(*nl)++;
		int i, j;
		words = stsplit(buf);
		for (j = 0; words[j] != NULL; j++)
			(*nw)++;
		i = strlen(buf);
		(*nc) += i;
		stfree(words);
	}
}

int main(UNUSED int argc, UNUSED char *argv[]) {
	int exitStatus = EXIT_SUCCESS;
	long nlines = 0L;
	long nchars = 0L;
	long nwords = 0L;

	countLWC(stdin, &nlines, &nwords, &nchars);

	printf("%8ld %8ld %8ld\n", nlines, nwords, nchars);
	return exitStatus;
}
