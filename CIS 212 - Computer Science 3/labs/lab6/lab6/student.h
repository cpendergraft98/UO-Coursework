#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <stdio.h>

typedef struct student {
    char *last;		
    char *middle;
    char *first;	
    char *year;	;
    char *major;
    char *duckid;	
    char *id;	
} Student;

/*
 * free up heap storage associated with `a'
 */
void freeStudent(Student *a);

/*
 * obtain next student from `fd'; returns NULL if at end of file
 */
Student *getStudent(FILE *fd);

/*
 * print student over three lines on `fd'
 */
void printStudent(Student *a, FILE *fd);

#endif /* _STUDENT_H_ */
