#ifndef _Y_ARRAY_LIST_H_
#define _Y_ARRAY_LIST_H_

#include "ycommon.h"

#ifdef __cplusplus
extern "C" {
#endif


#define Y_ARRAYLIST_DEFAULT_CAPACITY	10
#define Y_ARRAYLIST_INCREMENT_FACTOR	2


/*
 * Y Array List
 */
struct YArrayList {
	struct YListNode *nodes;
	long count;
	long capacity;
};

void YArrayListInit(struct YArrayList *list);
void YArrayListInitWithCapacity(struct YArrayList *list, long cap);
void YArrayListDestroy(struct YArrayList *list);

struct YArrayList *YArrayListNew(void);
struct YArrayList *YArrayListNewWithCapacity(long cap);
void YArrayListDelete(struct YArrayList *list);



#ifdef __cplusplus
}
#endif

#endif
