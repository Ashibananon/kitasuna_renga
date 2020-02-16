/*
 * Kitasuna Renga
 *
 * YArrayList Header File
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


#ifndef _Y_ARRAY_LIST_H_
#define _Y_ARRAY_LIST_H_

#include "ycommon.h"

#ifdef __cplusplus
extern "C" {
#endif


#define Y_ARRAYLIST_DEFAULT_CAPACITY	16

/*
 * Array list capacity increment parameters,
 * all in percentage.
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

/*
 * Initial array list.
 */
void YArrayListInit(struct YArrayList *list);

/*
 * Initial array list with given capacity.
 */
void YArrayListInitWithCapacity(struct YArrayList *list, long cap);

/*
 * Destroy array list.
 */
void YArrayListDestroy(struct YArrayList *list);

/*
 * Allocate a new array list.
 * Returns pointer to the list, or NULL if failed.
 */
struct YArrayList *YArrayListNew(void);

/*
 * Allocate a new array list with given capacity.
 * Returns pointer to the list, or NULL if failed.
 */
struct YArrayList *YArrayListNewWithCapacity(long cap);

/*
 * Release the given array list.
 */
void YArrayListDelete(struct YArrayList *list);

/*
 * Get node on the array list by index.
 * If error occurs, NULL is returned.
 */
struct YListNode *YArrayListAt(struct YArrayList *list, long index);

/*
 * Append the node after index on the list.
 * Returns 1 if succeeds.
 */
int YArrayListAppendAfterIndex(struct YArrayList *list,
			   long index,
			   struct YListNode *node);

/*
 * Insert the node before index on the list.
 * Returns 1 if succeeds.
 */
int YArrayListInsertBeforeIndex(struct YArrayList *list,
				long index,
				struct YListNode *node);

/*
 * Remove node at the given index of the list.
 * Returns the removed node if success, or NULL if failed.
 */
struct YListNode *YArrayListRemoveAt(struct YArrayList *list, long index);

/*
 * Returns count of the given list,
 * or -1 if error occurs.
 */
long YArrayListGetCount(struct YArrayList *list);


#ifdef __cplusplus
}
#endif

#endif
