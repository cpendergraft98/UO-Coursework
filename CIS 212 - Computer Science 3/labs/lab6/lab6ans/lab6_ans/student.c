#include "student.h"
#include <stdlib.h>
#include <string.h>

void freeStudent(Student *a) {
    free(a->first);
    free(a->last);
    free(a->middle);
    free(a->year);
    free(a->major);
    free(a->duckid);
    free(a->id);
    free(a);
}

Student *getStudent(FILE *fd) {
    Student *ans = NULL;
    char buf[BUFSIZ];
    char *f, *l, *m, *str, *ma, *d, *i;
    char first[10], last[50], year[50], major[50], duckid[25], id[15];
    char middle[10];
    if (fgets(buf, BUFSIZ, fd) != NULL) {
        l = strtok(buf, ","); strcpy(last, l);
        m = strtok(NULL, " \t\n"); strcpy(middle, m);
        f = strtok(NULL, " \t\n"); strcpy(first, f);
        (void) fgets(buf, BUFSIZ, fd);
        str = strtok(buf, "\n"); strcpy(year, str);
        (void) fgets(buf, BUFSIZ, fd);
        ma = strtok(buf, ","); strcpy(major, ma);
        d = strtok(NULL, " \t\n"); strcpy(duckid, d);
        i = strtok(NULL, " \t\n"); strcpy(id, i);
        ans = (Student *)malloc(sizeof(Student));
        if (ans != NULL) {
            ans->last = strdup(last);
            ans->first = strdup(first);
            ans->middle = strdup(middle);
            ans->year = strdup(year);
            ans->major = strdup(major);
            ans->duckid = strdup(duckid);
            ans->id = strdup(id);
        }
    }
    return ans;
}

void printStudent(Student *a, FILE *fd) {
    fprintf(fd, "%s, %s %s\n", a->last, a->middle, a->first);
    fprintf(fd, "%s\n", a->year);
    fprintf(fd, "%s, %s %s\n", a->major, a->duckid, a->id);
}
