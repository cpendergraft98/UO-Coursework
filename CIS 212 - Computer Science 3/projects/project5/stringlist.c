#include "stringlist.h"
#include <stdlib.h>

typedef struct sldata { 
    long capacity;
    long size;
    char **theArray;
    char (*freeValue)(void *e); 
} SLData;

static void sl_destroy(const StringList *sl) {
    SLData *sld = (SLData *)sl->self;

    for(long i = 0L; i < sld -> size; i++){
        free(sld -> theArray[i]);
    }
    
    free(sld -> theArray);
    free(sld);
    free((char *)sl);
}

static int sl_append(const StringList *sl, char *s) {
    SLData *sld = (SLData *)(sl->self);
    int status = (sld -> capacity > sld -> size);

    if(!status){
        size_t nbytes = 2 * sld -> capacity * sizeof(char *);
        char ** tmp = (char **)realloc(sld -> theArray, nbytes); 

        if( tmp != NULL){
            status = 1;
            sld -> theArray = tmp;
            sld -> capacity *= 2;
        }
    }
    if(status){
        sld -> theArray[sld -> size++] = s;
    }
    return status;
}

static int sl_get(const StringList *sl, long index, char **sptr) {
    SLData *sld = (SLData *)(sl->self);
    int status = (index >= 0L && index < sld -> size);

    if(status){
        *sptr = sld -> theArray[index];
    }
    return status;
}

static long sl_size(const StringList *sl) {
    SLData *sld = (SLData *)(sl->self);
    return sld -> size;
}

static StringList template = {
    NULL, sl_destroy, sl_append, sl_get, sl_size
};

const StringList *StringList_create(long capacity) {
    StringList *sl = (StringList *)malloc(sizeof(StringList));

    if(sl != NULL){
        SLData *sld = (SLData *)malloc(sizeof(SLData));
        if(sld != NULL){
            long cap = (capacity <= 0) ? DEFAULT_CAPACITY : capacity;
            char **array = (char **)malloc(cap * sizeof(void *)); /* change void to char? */

            if(array != NULL){
                sld -> capacity = cap;
                sld -> size = 0L;
                sld -> theArray = array;
                *sl = template;
                sl -> self = sld;
            } else {
                free(sld);
                free(sl);
                sl = NULL;
            }
        } else {
            free(sl);
            sl = NULL;
        }
    }
    return sl;
}
