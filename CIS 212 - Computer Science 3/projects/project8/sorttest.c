#include "sort.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define UNUSED __attribute__((unused))

int cmp(void *v1, void *v2) {
    return strcmp((char *)v1, (char *)v2);
}

int main(UNUSED int argc, UNUSED char *argv[]) {
    char *lines[4096];
    char buf[BUFSIZ];
    long i, n = 0L;

    while (fgets(buf, BUFSIZ, stdin) != NULL) {
        lines[n++] = strdup(buf);
    }
    sort((void **)lines, n, cmp);
    for (i = 0; i < n; i++) {
        printf("%s", lines[i]);
        free(lines[i]);
    }
    return EXIT_SUCCESS;
}
