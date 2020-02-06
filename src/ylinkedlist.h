#ifndef _Y_LINKED_LIST_H_
#define _Y_LINKED_LIST_H_

#include "ycommon.h"

#ifdef __cplusplus
extern "C" {
#endif


/*
 * Y Linked List
 */
struct YLinkedList {
	struct YListNode *head;
	struct YListNode *tail;
	long count;
};

void YLinkedListInit(struct YLinkedList *list);
void YLinkedListDestroy(struct YLinkedList *list);

struct YLinkedList *YLinkedListNew(void);
void YLinkedListDelete(struct YLinkedList *list);

int YLinkedListInsertHead(struct YLinkedList *list, struct YListNode *node);
int YLinkedListAppendTail(struct YLinkedList *list, struct YListNode *node);

int YLinkedListInsertBefore(struct YLinkedList *list,
				struct YListNode *pos,
				struct YListNode *node);

int YLinkedListAppendAfter(struct YLinkedList *list,
				struct YListNode *pos,
				struct YListNode *node);

struct YListNode *YLinkedListRemoveNode(struct YLinkedList *list, struct YListNode *node);


struct YListNode *YLinkedListGetHead(struct YLinkedList *list);
struct YListNode *YLinkedListGetTail(struct YLinkedList *list);
long YLinkedListGetCount(struct YLinkedList *list);


#ifdef __cplusplus
}
#endif

#endif
