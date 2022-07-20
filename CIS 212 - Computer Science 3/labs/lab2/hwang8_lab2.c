#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define UNUSED __attribute__((unused))
#define BUFFSIZE 1024

int main(int argc, char *argv[]){

	int option;
	extern int opterr;
	opterr = 0;
	int r = 0;
	char rem;

	while ((option = getopt(argc, argv, "r:")) != -1){
		switch(option){
			case 'r':
				rem = *optarg;
				printf("flag: -%c option: %c\n", option, rem);
				r = 1;
				break;
			case '?':
				printf("unknown flag: -%c\n", optopt);
				break;
		}
	
	}
	
	char buff[BUFFSIZE];
	int i = 0;
	int j;
	while ((fgets(buff, BUFFSIZE, stdin)) != NULL ){
		if (r){
			for(j = 0; j < (int)strlen(buff); j++){
				if (buff[j] == rem) {
					buff[j] = ' ';
				}
			}
		}
		printf("%d; %s", i, buff );
		i++;	
	}

	return EXIT_SUCCESS;
}
