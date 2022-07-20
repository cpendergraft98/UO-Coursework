#include <stdio.h>
#include <stdlib.h>
#include "ADTs/stringADT.h"
#include "ADTs/arraylist.h"
#include <stdbool.h>
#include <unistd.h>

void wordsperline(FILE *fp, bool flags[]){
	char buf[BUFSIZ];

	while(fgets(buf, sizeof buf, fp) != NULL){
		const String *stADT = String_create(buf);

		if(flags[0]){
			stADT -> lower(stADT);
		}

		if(flags[1]){
			stADT -> translate(stADT, "[:punct:]", ' ');
		}
		
		const ArrayList *al = stADT -> split(stADT, "");
		if (al == NULL){
			stADT -> destroy(stADT);
			continue;
		}
		
		const Iterator *it = al -> itCreate(al);
		while(it -> hasNext(it)){
			char *word;
			(void) it -> next(it, (void**)&word);
			printf("%s\n", word);
		}
		it -> destroy(it);
		al -> destroy(al);
		stADT -> destroy(stADT);
	}
}

int main(int argc, char *argv[]){
	int opt;
	FILE *fp;

	bool doConvert, doPunct, multiple_files;

	doConvert = doPunct = multiple_files = false;
	opterr = 0;
	while((opt = getopt(argc, argv, "lp")) != -1){
		switch(opt){
			case 'l': doConvert = true; break;
			case 'p': doPunct = true; break;
			default: fprintf(stderr, "%s: illegal option, '-%c'\n", argv[0], optopt);
			return EXIT_SUCCESS;
		}
	}
	bool flags[3] = {doConvert, doPunct, multiple_files};

	if(argv[optind] == NULL){
		wordsperline(stdin, flags);
		return EXIT_SUCCESS;

	}else{
		for(int i = optind; argv[i] != NULL; i++){
			fp = fopen(argv[i], "r");

			if (fp == NULL){
				fprintf(stderr, "Illegal file %s provided\n", argv[optind]);
				return EXIT_FAILURE;
			}

			wordsperline(fp, flags);
			fclose(fp);
	}
	return EXIT_SUCCESS;
	}
}