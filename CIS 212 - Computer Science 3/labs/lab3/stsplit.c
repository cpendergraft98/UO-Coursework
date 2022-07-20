#include "stsplit.h"
#include <stdlib.h>
#include <string.h>

char **stsplit(char *line) {
	char *b;
	char *w[101]; /* max of 99 words in a line */
	int i, n;
	char delim[] = " \t\n";
	char *p;
	char **ans;

	b = strdup(line); /* make a copy of the line on the heap */
	w[0] = b; /* remember that pointer in w[0] */
	p = strtok(b, delim);
	for (i = 1; p != NULL; i++, p = strtok(NULL, delim))
		w[i] = p;
	w[i] = NULL; /* add sentinel */
	n = i + 1;
	ans = (char **)malloc(n * sizeof(char *));
	for (i = 0; i < n; i++)
		ans[i] = w[i];
	return ans + 1; /* return pointer to the first word */
}

void stfree(char **words) {
	char **p = words - 1; /* point at actual start of block */
	free (p[0]); /* free the character buffer */
	free (p); /* free the array of pointers */
}
