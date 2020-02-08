#ifndef _Y_ARRAY_LIST_H_
#define _Y_ARRAY_LIST_H_

#include "ycommon.h"

#ifdef __cplusplus
extern "C" {
#endif


#define Y_ARRAYLIST_DEFAULT_CAPACITY	16

/*
 * Array list capacity increment parameters,
 * all in percentage
 */
#define Y_ARRAYLIST_INCREMENT_FACTOR	80
#define Y_ARRAYLIST_INCREMENT_THRESHOLD	80


/*
 * Y Array List
 */
struct YArrayList {
	struct YListNode **nodes;
	long count;
	long capacity;
};

void YArrayListInit(struct YArrayList *list);
void YArrayListInitWithCapacity(struct YArrayList *list, long cap);
void YArrayListDestroy(struct YArrayList *list);

struct YArrayList *YArrayListNew(void);
struct YArrayList *YArrayListNewWithCapacity(long cap);
void YArrayListDelete(struct YArrayList *list);

struct YListNode *YArrayListAt(struct YArrayList *list, long index);
long YArrayListGetIndex(struct YArrayList *list, struct YListNode *node);

int YArrayListAppendAfter(struct YArrayList *list,
			  struct YListNode *pos,
			  struct YListNode *node);

int YArrayListInsertBefore(struct YArrayList *list,
			   struct YListNode *pos,
			   struct YListNode *node);

int YArrayListAppendAfterIndex(struct YArrayList *list,
			   long index,
			   struct YListNode *node);

int YArrayListInsertBeforeIndex(struct YArrayList *list,
				long index,
				struct YListNode *node);

struct YListNode *YArrayListRemove(struct YArrayList *list, struct YListNode *node);
struct YListNode *YArrayListRemoveAt(struct YArrayList *list, long index);

long YArrayListGetCount(struct YArrayList *list);


#ifdef __cplusplus
}
#endif

#endif
