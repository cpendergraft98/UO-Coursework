#include "studentlist.h"
#include <stdlib.h>
#include <string.h>
typedef struct st_data{
	long capacity;
	long size;
	Student **array;
	(void) (*freeV)(void *);

}STData;

static void st_destroy(const StudentList *al) {
	STData *st = (STData *)al -> self;

	for(long i = 0L; i < st -> size; i++){
		st -> freeV(st -> array[i]);
	}
	free(st -> array);
	free(st);
	free((void *)al);
}

static bool st_add(const StudentList *al, Student *a) {
	STData *st = (STData*)al -> self;
	bool status = (st -> size < st -> capacity);

	if(!status){
		//realloc more memory
		size_t nbytes = 2 * st -> capacity * sizeof(Student *);
		Student ** tmp = (Student **)realloc(st -> array, nbytes);

		if( tmp != NULL){
			st -> array = tmp;
			st -> capacity *= 2;
			status = true;
		}
	}
	if(status){
		st -> array[st -> size++] = a;
	return status;
	}
}

static bool st_get(const StudentList *al, long index, Student **aptr) {
	STData *st = (STData *)al -> self;
	bool status = (0L <= index && index < st -> size);

	if(status){
		*aptr = st -> array[index];
	return status;
	}
}

static long st_size(const StudentList *al) {
	STData *st = (STData *)al -> self;
	return st -> size;
}

static StudentList template = {
	NULL, st_destroy, st_add, st_get, st_size
};

#define UNUSED __attribute__((unused))
static void doNothing(UNUSED void *x) {
}

const StudentList *StudentList_create(long capacity, void (*freeV)(void*)) {
	StudentList *al = (StudentList *)malloc(sizeof(StudentList));
	if(al != NULL){
		STData *st = ()malloc(sizeof(STData));
		if(st != NULL){
			long cap = (capacity <= 0L) ? DEFAULT_CAPACITY : capacity;
			student **array = (Student **)malloc(cap * sizeof(Student *));
			if( array != NULL) {
				st -> capacity = cap;
				st -> size = 0L;
				st -> array = array;
				st -> freeV = (freeV == NULL) ? doNothing : freeV;
				*al = template;
				al -> self = st;
			}else{
				free(st);
				free(al);
				al = NULL;
			}
		}else{
			free(al);
			al = NULL;
		}
	}
	return al;
}
