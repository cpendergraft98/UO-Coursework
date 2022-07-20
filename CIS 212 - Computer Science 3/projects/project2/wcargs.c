#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
	int opt;
	bool doChar, doLine, doWord, haveFlag;

	doChar = doLine = doWord = haveFlag = false;
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
		doChar = doWord = doLine = true;
	}
	if (doLine ==  true) {
		printf("Counting lines \n");
	}
	if (doWord == true) {
		printf("Counting words \n");
	}
	if (doChar == true) {
		printf("Counting characters \n");
	}
	if (argv[optind] != NULL) {
		printf("Processing standard input and no total line \n");
	}
	if(argv[optind] != NULL) {
		printf("Processing ");
		for (int i = optind; argv[i] != NULL; i++) {
			if (argv[i + 1] == NULL) {
				printf("%s ", argv[i]);
			}else{
				printf("%s, ", argv[i]);
			}
		}
		if (argv[optind + 1] == NULL) {
			printf("and no total line. \n");
		}else{
			printf("and a total line. \n");
		}
	}
	return EXIT_SUCCESS;
}