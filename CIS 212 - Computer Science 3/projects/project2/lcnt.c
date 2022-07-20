#include <stdio.h>
#include <stdlib.h>
#define UNUSED __attribute__((unused))

int main(UNUSED int argc, UNUSED char *argv[]) {
	long nlines = 0L;
	char buf[BUFSIZ];
	int exitStatus = EXIT_SUCCESS;

	while (fgets(buf, sizeof buf, stdin) != NULL)
		nlines++;
	printf("%8ld\n", nlines);
	return exitStatus;
}
