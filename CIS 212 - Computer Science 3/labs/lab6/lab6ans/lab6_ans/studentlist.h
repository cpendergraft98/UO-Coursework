#ifndef _STUDENTLIST_H_
#define _STUDENTLIST_H_

#include "student.h"
#include <stdbool.h>
#include "ADTs/iterator.h"
#define DEFAULT_CAPACITY 50

typedef struct studentlist StudentList;

const StudentList *StudentList_create(long capacity, void (*freeV)(void*));

struct studentlist {
    void *self;
    void (*destroy)(const StudentList *al);
    bool (*add)(const StudentList *al, Student *a);
    bool (*get)(const StudentList *al, long index, Student **aptr);
    long (*size)(const StudentList *al);
};

#endif /* STUDENTTLIST_H_ */
