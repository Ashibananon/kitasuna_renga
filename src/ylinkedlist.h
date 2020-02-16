/*
 * Kitasuna Renga
 *
 * YLinkedList Header File
 *
 * Copyright(C) 2020 Ashibananon(Yuan).
 *
 *
 * This file is part of Kitasuna Renga.
 *
 * Kitasuna Renga is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Kitasuna Renga is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Kitasuna Renga.  If not, see <https://www.gnu.org/licenses/>.
 *
 */


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

/*
 * Initialize the given list.
 */
void YLinkedListInit(struct YLinkedList *list);

/*
 * Destroy the given list.
 */
void YLinkedListDestroy(struct YLinkedList *list);

/*
 * Allocate a new linked list.
 * Returns pointer to the list, or NULL if failed.
 */
struct YLinkedList *YLinkedListNew(void);

/*
 * Release the given linked list.
 */
void YLinkedListDelete(struct YLinkedList *list);

/*
 * Insert the given node to the head of the given list.
 * Returns 1 if success.
 */
int YLinkedListInsertHead(struct YLinkedList *list, struct YListNode *node);

/*
 * Append the given node to the tail of the given list.
 * Returns 1 if success.
 */
int YLinkedListAppendTail(struct YLinkedList *list, struct YListNode *node);

/*
 * Insert the given node before pos of the list.
 * Returns 1 if success.
 */
int YLinkedListInsertBefore(struct YLinkedList *list,
			struct YListNode *pos,
			struct YListNode *node);

/*
 * Append the given node after pos of the list.
 * Returns 1 if success.
 */
int YLinkedListAppendAfter(struct YLinkedList *list,
			struct YListNode *pos,
			struct YListNode *node);

/*
 * Remove the node from list.
 * Returns 1 if success.
 */
struct YListNode *YLinkedListRemoveNode(struct YLinkedList *list, struct YListNode *node);

/*
 * Linked list getter for list head.
 */
struct YListNode *YLinkedListGetHead(struct YLinkedList *list);

/*
 * Linked list getter for list tail.
 */
struct YListNode *YLinkedListGetTail(struct YLinkedList *list);

/*
 * Linked list getter for count.
 */
long YLinkedListGetCount(struct YLinkedList *list);


#ifdef __cplusplus
}
#endif

#endif
