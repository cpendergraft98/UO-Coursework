/* include is used to import libraries i.e. #include <library>
 * and head files i.e. #include "header file"
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "stsplit.h"

#define UNUSED __attribute__((unused))
#define BUFSIZE 1024

int main(int argc, char *argv[]) {

	int option;
	int flag = 0;
	char rem_char; //character to be removed

	extern int opterr;
	opterr = 0;

	while((option = getopt(argc, argv, "c:")) != -1) { //note the : after c
		switch(option) {
			case 'c':
				rem_char = *optarg;
				printf("Flag: -%c Option: %c\n", option, rem_char);
				flag = 1;
				break;
			case '?':
				printf("Unknown flag: -%c\n", optopt);
				break;
		}
	}

	char buf[BUFSIZE];
	int i = 0;

	while (fgets(buf, BUFSIZE, stdin) != NULL){
		if(flag == 1) {
			for(int j = 0; j < (int)strlen(buf); j++){
				if(buf[j] == rem_char) {
					buf[j] = ' ';
				}
			}
		}
		printf("%d: %s", i, buf);
		i++;
	}
	return EXIT_SUCCESS;
}
