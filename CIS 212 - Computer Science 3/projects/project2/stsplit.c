#include "stsplit.h"
#include <stdlib.h>
#include <string.h>

char **stsplit(char *line) {
	char *b;
	char *w[101];
	int i, n;
	char delim[] = " \t\n";
	char *p;
	char **ans;

	b = strdup(line);
	w[0] = b;
	p = strtok(b, delim);
	for (i = 1; p != NULL; i++, p = strtok(NULL, delim))
		w[i] = p;
	w[i] = NULL;
	n = i + 1;
	ans = (char **)malloc(n * sizeof(char *));
	for (i = 0; i < n; i++)
		ans[i] = w[i];
	return ans + 1;
}

void stfree(char **words) {
	char **p = words - 1;
	free (p[0]);
	free (p);
}
