#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
	int opt;
	bool doChar, doLine, doWord, haveFlag;

	doChar = doLine = doWord = haveFlag = false;
	opterr = 0;
	while((opt = getopt(argc, argv, "clw"))!= -1) {
		switch(opt){
			case 'c': doChar = haveFlag = true; break;
			case 'l': doLine = haveFlag = true; break;
			case 'w': doWord = haveFlag = true; break;
			default: fprintf(stderr, "%s: illegal option, '-%c'\n", argv[0], optopt);
		}
	}
	if(doLine = true){
		printf("Counting Lines \n");
	}
	if(doWord = true){
		printf("Counting Words \n");
	}
	if (doChar = true){
		printf("Counting Characters \n");
	}
	if (! haveFlag){
		doChar = doLine =doWord = true;
	}
	if(argv[0] != NULL && argv[1] == NULL){
		printf("Processing standard input and no total line \n");
	}
	if(argv[0] != NULL && argv[1] != NULL){
		printf("Processing ");
		for (int i = 1; argv[i] != NULL; i++) {
			printf("%s, ", argv[i]);
		}
			printf("and a total line\n");
	}		
	return EXIT_SUCCESS;
}