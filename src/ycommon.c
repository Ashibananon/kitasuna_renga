#include <stdlib.h>

#include "ycommon.h"

/*
 * Y List Node implementation
 */
struct YListNode *YListNodeNew()
{
	struct YListNode *node = (struct YListNode *)malloc(sizeof(struct YListNode));
	if (node != NULL) {
		node->data = NULL;
		node->pre = NULL;
		node->next = NULL;
		node->destroyer = NULL;
	}

	return node;
}


struct YListNode *YListNodeNewWithData(void *d, USERDATA_DESTROYER destroyer)
{
	struct YListNode *node = (struct YListNode *)malloc(sizeof(struct YListNode));
	if (node != NULL) {
		node->data = d;
		node->pre = NULL;
		node->next = NULL;
		node->destroyer = destroyer;
	}

	return node;
}


void YListNodeDelete(struct YListNode *node)
{
	if (node != NULL) {
		if (node->destroyer != NULL) {
			node->destroyer(node->data);
			node->data = NULL;
		}

		free(node);
	}
}


void *YListNodeGetData(struct YListNode *node)
{
	void *ret = NULL;
	if (node != NULL)
		ret = node->data;

	return ret;
}


void YListNodeSetData(struct YListNode *node, void *d)
{
	if (node != NULL)
		node->data = d;
}


void YListNodeSetDestroyer(struct YListNode *node, USERDATA_DESTROYER destroyer)
{
	if (node != NULL)
		node->destroyer = destroyer;
}


USERDATA_DESTROYER YListNodeGetDestroyer(struct YListNode *node)
{
	USERDATA_DESTROYER ret = NULL;
	if (node != NULL)
		ret = node->destroyer;

	return ret;
}
