#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "stsplit.h"

void printLWC(char *name, bool flags[], long counts[]) {
	int i;
	for (i = 0; i <= 2; i++){
		if (flags[i]){
			printf("%8ld", counts[i]);
		}
	}
	if(strcmp(name, "stdin") != 0){
		printf("%s\n", name);
	}else{
		printf("\n");
	}
}

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

int main(int argc, char *argv[]) {
	int opt;
	bool doChar, doLine, doWord, haveFlag;
	long nlines = 0L;
	long nwords = 0L;
	long nchars = 0L;
	long tlines = 0L;
	long twords = 0L;
	long tchars = 0L;
	FILE *fp;

	doLine = doChar = doWord = haveFlag = false;
	opterr = 0;

	while ((opt = getopt(argc, argv, "clw")) != -1) {
		switch(opt) {
			case 'c': doChar = haveFlag = true; break;
			case 'l': doLine = haveFlag = true; break;
			case 'w': doWord = haveFlag = true; break;
			default: fprintf(stderr, "%s: illegal option, '-%c'\n", argv[0], optopt);
		}
	}
	if (! haveFlag) {
		doChar = doLine = doWord = true;
	}
	bool flag[3] = {doLine, doWord, doChar};

	if (argv[optind] == NULL) {
			countLWC(stdin, &nlines, &nwords, &nchars);
			long counts[3] = {nlines, nwords, nchars};
			printLWC(" stdin ", flag, counts);
	}
	if (argv[optind] != NULL) {
		for(int i = optind; argv[i] != NULL; i++){
			if (strcmp(argv[i], "-") == 0){
				countLWC(fp, &nlines, &nwords, &nchars);
				long counts[3] = {nlines, nwords, nchars};
				printLWC(" stdin ", flag, counts);
			}else{
				fp = fopen(argv[i], "r");
				if(access(argv[i], F_OK) != 0){
					printf("./wc: open(%s) error \n", argv[i]);
					return EXIT_FAILURE;
				}
				countLWC(fp, &nlines, &nwords, &nchars);
				long counts[3] = {nlines, nwords, nchars};
				printLWC (argv[i] , flag, counts);
				tlines += nlines;
				twords += nwords;
				tchars += nchars;
				nlines = nwords = nchars = 0;
				if(argv[i+1] == NULL && argv[optind + 1] != NULL) {
					long counts[3] = {tlines, twords, tchars};
					printLWC(" Total ", flag, counts);
				}
			}
		}
		fclose(fp);
		return EXIT_SUCCESS;
	}
}