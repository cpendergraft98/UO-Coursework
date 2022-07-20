#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int exitStatus = EXIT_FAILURE;
    FILE *fd = NULL;
    Student *a = NULL;

    if (argc != 2) {
        fprintf(stderr, "usage: %s student_file\n", argv[0]);
        goto cleanup;
    }
    fd = fopen(argv[1], "r");
    if (fd == NULL) {
        fprintf(stderr, "%s: cannot open(%s)\n", argv[0], argv[1]);
        goto cleanup;
    }
    while ((a = getStudent(fd)) != NULL) {
        printStudent(a, stdout);
        freeStudent(a);
    }
    exitStatus = EXIT_SUCCESS;
cleanup:
    if (fd != NULL)
        fclose(fd);
    return exitStatus;
}
