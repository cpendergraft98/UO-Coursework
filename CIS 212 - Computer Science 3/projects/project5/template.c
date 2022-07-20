#include "stringlist.h"
#include "stdlib.h"

typedef struct sldata {          /* data for each instance */
    /* you must define the instance-specific fields for each StringList */
} SLData;

/* any helper functions needed by the methods */

static void sl_destroy(const StringList *sl) {
    SLData *sld = (SLData *)sl->self;

    /* the body of the destroy() method */
}

static int sl_append(const StringList *sl, char *s) {
    SLData *sld = (SLData *)sl->self;

    /* the body of the append() method - it must grow the capacity of
       the stringlist if you have run out of room */
}

static int sl_get(const StringList *sl, long index, char **sptr) {
    SLData *sld = (SLData *)sl->self;

    /* the body of the get() method */
}

static long sl_size(const StringList *sl) {
    SLData *sld = (SLData *)sl->self;

    /* the body of the size() method */
}

static StringList template = {
    NULL, sl_destroy, sl_append, sl_get, sl_size
};

const StringList *StringList_create(long capacity) {/* use default if 0L */

    /* the body of the constructor */
}
