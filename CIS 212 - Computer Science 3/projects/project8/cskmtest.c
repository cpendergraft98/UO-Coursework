/*
 * a simple test program showing how to use the C string key Map
 *
 * usage: ./cskmtest
 *
 * reads each line of input from standard input; puts a (key,value) pair
 * into the map; the key is the string "line %03ld", where the number
 * of the line replaces 03ld, and the value is the line read from
 * standard input
 *
 * After collecting all of the lines into the map, it uses an iterator to
 * print out the lines in iterator order.
 *
 * Then it sorts the lines by key, and prints those out.
 *
 * Finally, it sorts the lines by value, and prints those out.
 */
#include "ADTs/hashcskmap.h"
#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int keycmp(void *x1, void *x2) {
    MEntry *m1 = (MEntry *)x1;
    MEntry *m2 = (MEntry *)x2;
    return strcmp((char *)m1->key, (char *)m2->key);
}

int valcmp(void *x1, void *x2) {
    MEntry *m1 = (MEntry *)x1;
    MEntry *m2 = (MEntry *)x2;
    return strcmp((char *)m1->value, (char *)m2->value);
}

#define UNUSED __attribute__((unused))

int main(UNUSED int argc, UNUSED char *argv[]) {
    char buf[BUFSIZ];
    long i, n;
    const CSKMap *m = HashCSKMap(0L, 0.0, free);
    const Iterator *it;
    MEntry **mes;

    for (n = 0L; fgets(buf, BUFSIZ, stdin) != NULL; n++) {
        char key[25];
        char *s = strdup(buf);
        sprintf(key, "line %03ld", n);
        if (! m->putUnique(m, key, s)) {
            free(s);
        }
    }
    printf("=====Printing lines in iterator order\n");
    it = m->itCreate(m);
    while (it->hasNext(it)) {
        MEntry *me;
        (void)it->next(it, (void **)&me);
        printf("%s", (char *)me->value);
    }
    it->destroy(it);
    mes = m->entryArray(m, &n);
    sort((void **)mes, n, keycmp);
    printf("=====Printing lines in key order\n");
    for (i = 0; i <n; i++)
        printf("%s", (char *)mes[i]->value);
    sort((void **)mes, n, valcmp);
    printf("=====Printing lines in value order\n");
    for (i = 0; i <n; i++)
        printf("%s", (char *)mes[i]->value);
    free((void *)mes);
    m->destroy(m);
    return EXIT_SUCCESS;
}
