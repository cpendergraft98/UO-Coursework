#include <stdio.h>
#include <stdlib.h>
#define UNUSED __attribute__((unused))
#include <string.h>

int main(UNUSED int argc, UNUSED char *argv[]) {
	long nchars = 0L;
	char buf[BUFSIZ];
	int exitStatus = EXIT_SUCCESS;
	int i;

	while (fgets(buf, sizeof buf, stdin) != NULL){
		i = strlen(buf);
		nchars = nchars +i;
	}
	printf("%8ld\n", nchars);
	return exitStatus;
}
