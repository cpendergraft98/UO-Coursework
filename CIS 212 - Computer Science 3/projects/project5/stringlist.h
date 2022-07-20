#ifndef _STRINGLIST_H_
#define _STRINGLIST_H_

/*
 * interface to a StringList ADT
 */
#include "ADTs/iterator.h"
#define DEFAULT_CAPACITY 50L /* default initial capacity */

typedef struct stringlist StringList; /* define synonym */

const StringList *StringList_create(long capacity); /* use default if 0 */

struct stringlist{
	void *self;

   /*
 	* destroy the StringList, invoking free() on each element
	*/

	void (*destroy)(const StringList *sl);

	/*
	 * append string (allocated from the heap) to the StringList
	 * grow the capacity of the list, if necessary
	 *
	 * returns true (non-zero) if the string was successfully appended to the
	 * list, false (zero) if the append was unsuccessful
	 */

	int (*append)(const StringList *sl, char *s);

	/*
	 *retrieve string at 'index' from the StringList
	 *
	 *returns true (non-zero) if 'index' was legal, false (zero) if not
	 */

	int (*get)(const StringList *sl, long index, char **sptr);

	/*
	 * return the number of strings  in the list, N;
	 * legal indicies: 0 <= index < N
	 */

	long (*size)(const StringList *sl);
};
#endif /* _STRINGLIST_H_ */