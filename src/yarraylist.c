#include <stdlib.h>

#include "yarraylist.h"

void YArrayListInit(struct YArrayList *list)
{
	if (list != NULL) {
		list->nodes =
				(struct YListNode *)malloc(sizeof(struct YListNode) * Y_ARRAYLIST_DEFAULT_CAPACITY);
		if (list->nodes != NULL) {
			list->count = 0;
			list->capacity = Y_ARRAYLIST_DEFAULT_CAPACITY;
		}
	}
}


void YArrayListInitWithCapacity(struct YArrayList *list, long cap)
{
	if (list != NULL && cap > 0) {
		list->nodes =
				(struct YListNode *)malloc(sizeof(struct YListNode) * cap);
		if (list->nodes != NULL) {
			list->count = 0;
			list->capacity = cap;
		}
	}
}


void YArrayListDestroy(struct YArrayList *list)
{
	long i;
	struct YListNode *tmp;
	if (list != NULL) {
		for (i = 0; i < list->count; i++) {
			tmp = list->nodes + i;
			if (tmp->destroyer != NULL) {
				tmp->destroyer(tmp->data);
				tmp->data = NULL;
			}
		}

		free(list->nodes);
	}
}


struct YArrayList *YArrayListNew(void)
{
	struct YArrayList *list = (struct YArrayList *)malloc(sizeof(struct YArrayList));
	if (list != NULL)
		YArrayListInit(list);

	return list;
}


struct YArrayList *YArrayListNewWithCapacity(long cap)
{
	if (cap <= 0)
		return NULL;

	struct YArrayList *list = (struct YArrayList *)malloc(sizeof(struct YArrayList));
	if (list != NULL)
		YArrayListInitWithCapacity(list, cap);

	return list;
}


void YArrayListDelete(struct YArrayList *list)
{
	if (list != NULL) {
		YArrayListDestroy(list);
		free(list);
	}
}
