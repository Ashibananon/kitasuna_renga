#include <stdlib.h>

#include "ylinkedlist.h"


/*
 * Y Linked List implementation
 */
static long _ylinkedlist_delete_all_nodes(struct YLinkedList *list)
{
	struct YListNode *cur;
	while ((cur = list->head) != NULL) {
		list->head = list->head->next;
		list->head->pre = NULL;
		cur->next = NULL;
		if (list->head != NULL)
			list->head->pre = NULL;

		list->count--;

		YListNodeDelete(cur);
	}

	return list->count;
}

void YLinkedListInit(struct YLinkedList *list)
{
	if (list != NULL) {
		list->head = NULL;
		list->tail = NULL;
		list->count = 0;
	}
}


void YLinkedListDestroy(struct YLinkedList *list)
{
	if (list != NULL) {
		_ylinkedlist_delete_all_nodes(list);
	}
}


struct YLinkedList *YLinkedListNew()
{
	struct YLinkedList *list = (struct YLinkedList *)malloc(sizeof(struct YLinkedList));
	if (list != NULL) {
		list->head = NULL;
		list->tail = NULL;
		list->count = 0;
	}

	return list;
}


void YLinkedListDelete(struct YLinkedList *list)
{
	if (list != NULL) {
		_ylinkedlist_delete_all_nodes(list);
		free(list);
	}
}


static int _check_node_on_list(struct YLinkedList *list, struct YListNode *node)
{
	int ret = -1;
	struct YListNode *cur = list->head;
	if (cur == NULL && cur == node) {
		ret = 0;
	} else {
		while (cur != NULL) {
			if (cur == node) {
				ret = 0;
				break;
			}

			cur = cur->next;
		}
	}

	return ret;
}


int YLinkedListInsertBefore(struct YLinkedList *list,
				struct YListNode *pos,
				struct YListNode *node)
{
	if (list == NULL || node == NULL)
		return 0;

	if (_check_node_on_list(list, pos) != 0)
		return 0;

	if (list->count == 0) {
		list->head = node;
		list->tail = node;
		list->count++;

		return 1;
	}

	if (pos->pre != NULL) {
		pos->pre->next = node;
	} else {
		list->head = node;
	}
	node->pre = pos->pre;
	node->next = pos;
	pos->pre = node;

	list->count++;

	return 1;
}


int YLinkedListAppendAfter(struct YLinkedList *list,
				struct YListNode *pos,
				struct YListNode *node)
{
	if (list == NULL || node == NULL)
		return 0;

	if (_check_node_on_list(list, pos) != 0)
		return 0;

	if (list->count == 0) {
		list->head = node;
		list->tail = node;
		list->count++;

		return 1;
	}

	if (pos->next != NULL) {
		pos->next->pre = node;
	} else {
		list->tail = node;
	}
	node->next = pos->next;
	node->pre = pos;
	pos->next = node;

	list->count++;

	return 1;
}


int YLinkedListInsertHead(struct YLinkedList *list, struct YListNode *node)
{
	if (list == NULL || node == NULL)
		return 0;

	return YLinkedListInsertBefore(list, list->head, node);
}


int YLinkedListAppendTail(struct YLinkedList *list, struct YListNode *node)
{
	if (list == NULL || node == NULL)
		return 0;

	return YLinkedListAppendAfter(list, list->tail, node);
}


struct YListNode *YLinkedListRemoveNode(struct YLinkedList *list, struct YListNode *node)
{
	struct YListNode *ret = NULL;

	if (list == NULL || node == NULL)
		return ret;
	if (_check_node_on_list(list, node) != 0)
		return ret;

	if (list->count == 1) {
		list->head = NULL;
		list->tail = NULL;
		list->count--;
		ret = node;
	} else {
		if (list->head == node) {
			list->head = list->head->next;
			list->head->pre = NULL;
			node->next = NULL;
			list->count--;
			ret = node;
		} else if (list->tail == node) {
			list->tail = list->tail->pre;
			list->tail->next = NULL;
			node->pre = NULL;
			list->count--;
			ret = node;
		} else {
			node->pre->next = node->next;
			node->next->pre = node->pre;
			node->pre = NULL;
			node->next = NULL;
			list->count--;
			ret = node;
		}
	}

	return ret;
}


struct YListNode *YLinkedListGetHead(struct YLinkedList *list)
{
	if (list == NULL)
		return NULL;
	return list->head;
}


struct YListNode *YLinkedListGetTail(struct YLinkedList *list)
{
	if (list == NULL)
		return NULL;
	return list->tail;
}


long YLinkedListGetCount(struct YLinkedList *list)
{
	if (list == NULL)
		return -1;
	return list->count;
}
