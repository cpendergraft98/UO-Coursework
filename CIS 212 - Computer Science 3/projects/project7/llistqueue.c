/*
 * implementation for linked-list-based generic FIFO queue
 */
#include "ADTs/queue.h"
#include <stdlib.h>

typedef struct qnode{
    struct qnode *next;
    void *value;
}QNode;

typedef struct q_data {
   int (*cmp);
   long size;
   QNode *head;
   QNode *tail;
   void (*freeValue)(void *v);
} QData;

static void purge(QData *qd, void(*freeV)(void *e)){
    if(freeV != NULL){
        QNode *p;
        for(p = qd -> head; p != NULL; p = p -> next)
            (*freeV)(p -> value);
    }
}

static void freeList(QData *qd){
    QNode *p, *n = NULL;
    for(p = qd -> head; p != NULL; p = n){
        n = p -> next;
        free(p);
    }
}

static void q_destroy(const Queue *q) {
    QData *qd = (QData *)q -> self;
    purge(qd, qd -> freeValue);
    freeList(qd);
    free(qd);
    free((void *)q);
}

static void q_clear(const Queue *q) {
    QData *qd = (QData *)q -> self;
    purge(qd, qd -> freeValue);
    freeList(qd);
    free(qd);
    qd -> head = qd -> tail = NULL;
    qd -> size = 0L;
}

static int q_enqueue(const Queue *q, void *element) {
    QData *qd = (QData *)q -> self;
    QNode *new = (QNode *)malloc(sizeof(QNode));
    int status = (new != NULL);

    if(status){
        QNode *prev = NULL, *next;
        new -> next = NULL;
        new -> value = element;
        if(qd -> size == 0){
            qd -> head = new;
            qd -> tail = new;
        }else{
            qd -> tail -> next = new;
            qd -> tail = new;
         }
    }
    qd -> size++;
    return status;
}

static int q_front(const Queue *q, void **element) {
     QData *qd = (QData *)q -> self;
     int status = (qd -> size > 0L);

     if(status)
        *element = qd -> head -> value;

    return status;
}

static int q_dequeue(const Queue *q, void **element) {
    QData *qd = (QData *)q -> self;
    int status = (qd -> size > 0L);

    if(status){
        QNode *p = qd -> head;
        if((qd -> head = p -> next) == NULL)
            qd -> tail = NULL;
        *element = p -> value;
        qd -> size--;
        free(p);
    }
    return status;
}

static long q_size(const Queue *q) {
    QData *qd = (QData *)q -> self;
    return qd -> size;
}

static int q_isEmpty(const Queue *q) {
    QData *qd = (QData *)q -> self;
    return (qd -> size == 0L);
}

static void **genArray(QData *qd){
    void **theArray = NULL;
    if(qd -> size > 0L){
        theArray = (void **)malloc(qd -> size*sizeof(void *));
        if(theArray != NULL){
            long i = 0L;
            QNode *p;
            for(p = qd -> head; p != NULL; p = p -> next)
                theArray[i++] = p -> value;
        }
    }
    return theArray;
}

static void **q_toArray(const Queue *q, long *len) {
	QData *qd = (QData *)q -> self;
    void **tmp = genArray(qd);
    if(tmp != NULL)
        *len = qd -> size;
    return tmp;
}

static const Iterator *q_itCreate(const Queue *q) {
	QData *qd = (QData *)q -> self;
	const Iterator *it = NULL;
	void **tmp = genArray(qd);
	if(tmp != NULL){
		it = Iterator_create(qd -> size, tmp);
		if(it == NULL)
			free(tmp);
	}
	return it;
}

static const Queue *q_create(const Queue *q);

static Queue template = {
    NULL, q_create, q_destroy, q_clear, q_enqueue, q_front, q_dequeue, q_size,
    q_isEmpty, q_toArray, q_itCreate
};

static void doNothing(__attribute__((unused))void *e){
}

static const Queue *newQueue(void(*freeV)(void*)){
    Queue *q = (Queue *)malloc(sizeof(Queue));

    if(q != NULL){
        QData *qd = (QData *)malloc(sizeof(QData));
        if(qd != NULL){
            qd -> size = 0L;
            qd -> head = NULL;
            qd -> tail = NULL;
            qd -> freeValue = (freeV != NULL) ? freeV : doNothing;
            *q = template;
            q -> self = qd;
        }else{
            free(q);
            q = NULL;
        }
    }
    return q;
}

static const Queue *q_create(const Queue *q) {
    QData *qd = (QData *)q -> self;

    return newQueue(qd -> freeValue);
}

const Queue *LListQueue(void (*freeValue)(void *e)) {

    return newQueue(freeValue);
}

const Queue *Queue_create(void (*freeValue)(void *e)) {\

    return newQueue(freeValue);
}
