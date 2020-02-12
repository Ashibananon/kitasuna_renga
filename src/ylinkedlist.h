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
