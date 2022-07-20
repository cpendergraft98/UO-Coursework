#include "stringlist.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define UNUSED __attribute__((unused))

int main(UNUSED int argc, UNUSED char *argv[]){
	const StringList *sl;
	char buf[BUFSIZ];
	long index;

	if((sl = StringList_create(0L)) == NULL){
		fprintf(stderr, "Unable to create StringList to hold input lines\n");
		return EXIT_FAILURE;
	}
	while(fgets(buf, sizeof buf, stdin) != NULL){
		char *sp = strdup(buf);
		if(!(sl -> append(sl, sp))){
			fprintf(stderr, "Unable to append line to StringList: %s", sp);
			sl -> destroy(sl);
			return EXIT_FAILURE;
		}
	}
	int i = sl -> size(sl);
	for(index = i-1; index >= 0; index--){
		char *sp;

		if(!(sl -> get(sl, index, (char **)&sp))){
			fprintf(stderr, "Unable to retrieve line %ld\n", index);
			sl -> destroy(sl);
			return EXIT_FAILURE;
		}
		printf("%s", sp);
	}
	sl -> destroy(sl);
	return EXIT_SUCCESS;
}