#include "stringlist.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	const StringList *sl;
	int i;
	long lvalue;

	if((sl = StringList_create(50L)) == NULL){
		fprintf(stderr, "%s: Unable to create StringList\n", argv[0]);
		return EXIT_FAILURE;
	}
	for(index = 1; index < argc; index++){
		long l;
		sscanf(argv[index], "%ld", &l);
		sl -> append(sl, l);
	}
	for(index = 0; sl -> get(sl, &lvalue); index++)
		printf("%s%ld", (index == 0) ? "" : " ", lvalue);
	if (index > 0)
		printf("\n");
	sl -> destroy(sl);

	return EXIT_SUCCESS;
}