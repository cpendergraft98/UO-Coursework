#include "ADTs/arraylist.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define UNUSED __attribute__((unused))

int main(UNUSED int argc, UNUSED char *argv[]){
	const ArrayList *al = ArrayList_create(0L, free);
	char buf[BUFSIZ];
	long index;

	if(al == NULL){
		fprintf(stderr, "Unable to create ArrayList to hold input lines\n");
		return EXIT_FAILURE;
	}
	while(fgets(buf, sizeof buf, stdin) != NULL){
		char *sp = strdup(buf);
		if(!(al -> add(al, sp))){
			fprintf(stderr, "Unable to append line to ArrayList: %s", sp);
			al -> destroy(al);
			return EXIT_FAILURE;
		}
	}
	int i = al -> size(al);
	for(index = i-1; index >= 0; index--){
		char *sp;

		if(!(al -> get(al, index, (void **)&sp))){
			fprintf(stderr, "Unable to retrieve line %ld\n", index);
			al -> destroy(al);
			return EXIT_FAILURE;
		}
		printf("%s", sp);
	}
	al -> destroy(al);
	return EXIT_SUCCESS;
}