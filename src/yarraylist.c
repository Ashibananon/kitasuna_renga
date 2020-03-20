/*
 * Kitasuna Renga
 *
 * YArrayList Source File
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


#include <stdlib.h>

#include "yarraylist.h"

void YArrayListInit(struct YArrayList *list)
{
	if (list != NULL) {
		list->nodes =
			(struct YListNode **)malloc(sizeof(struct YListNode *) * Y_ARRAYLIST_DEFAULT_CAPACITY);
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
			(struct YListNode **)malloc(sizeof(struct YListNode *) * cap);
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
			tmp = *(list->nodes + i);
			YListNodeDeleteWithData(tmp);
			*(list->nodes + i) = NULL;
		}
		list->count -= i;

		free(list->nodes);
		list->nodes = NULL;
		list->capacity = 0;
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


struct YListNode *YArrayListAt(struct YArrayList *list, long index)
{
	if (list == NULL)
		return NULL;

	if (index < 0 || index > list->count - 1)
		return NULL;

	return *(list->nodes + index);
}


static long _array_list_get_index(struct YArrayList *list, struct YListNode *node)
{
	long ret = -1;
	long i;
	if (list == NULL || node == NULL)
		return ret;

	for (i = 0; i < list->count; i++) {
		if (*(list->nodes + i) == node) {
			ret = i;
			break;
		}
	}

	return ret;
}


static int _array_list_append_after_node(struct YArrayList *list,
			struct YListNode *pos,
			struct YListNode *node)
{
	if (list == NULL || node == NULL)
		return 0;

	return YArrayListAppendAfterIndex(list,
					_array_list_get_index(list, pos),
					node);
}


static int _array_list_insert_before_node(struct YArrayList *list,
			struct YListNode *pos,
			struct YListNode *node)
{
	if (list == NULL || node == NULL)
		return 0;

	return YArrayListInsertBeforeIndex(list,
					_array_list_get_index(list, pos),
					node);
}


static int _arraylist_increase_capacity(struct YArrayList *list, long inc)
{
	int ret = -1;

	struct YListNode **tmp = list->nodes;
	long tmp_cnt = list->count;
	long tmp_cap = list->capacity;

	if ((tmp_cnt + inc) * 100
		> tmp_cap * Y_ARRAYLIST_INCREMENT_THRESHOLD ) {
		/* Calculate increased capacity */
		long last_cap;
		long inc_cap = tmp_cap + tmp_cap * Y_ARRAYLIST_INCREMENT_FACTOR / 100;
		while (inc_cap <= tmp_cap + inc) {
			last_cap = inc_cap;
			inc_cap = inc_cap + inc_cap * Y_ARRAYLIST_INCREMENT_FACTOR / 100;
			if (inc_cap <= last_cap)
				inc_cap++;
		}

		long i;
		list->nodes = (struct YListNode **)
				malloc(sizeof(struct YListNode *) * inc_cap);
		if (list->nodes != NULL) {
			for (i = 0; i < tmp_cnt; i++)
				*(list->nodes + i) = *(tmp + i);

			list->count = tmp_cnt;
			list->capacity = inc_cap;

			free(tmp);

			ret = 0;
		}
	} else {
		ret = 0;
	}

	return ret;
}

int YArrayListAppendAfterIndex(struct YArrayList *list,
			long index,
			struct YListNode *node)
{
	int ret = 0;

	long i;
	if (list == NULL || node == NULL)
		return ret;

	if (_arraylist_increase_capacity(list, 1) != 0)
		return ret;

	if (list->count == 0) {
		*(list->nodes + list->count) = node;
		list->count++;
		ret = 1;
	} else if (index >= 0 && index < list->count) {
		for (i = list->count; i > index + 1; i--) {
			*(list->nodes + i) = *(list->nodes + i - 1);
		}
		*(list->nodes + index + 1) = node;
		list->count++;
		ret = 1;
	}

	return ret;
}


int YArrayListInsertBeforeIndex(struct YArrayList *list,
				long index,
				struct YListNode *node)
{
	int ret = 0;

	long i;
	if (list == NULL || node == NULL)
		return ret;

	if (_arraylist_increase_capacity(list, 1) != 0)
		return ret;

	if (list->count == 0) {
		*(list->nodes + list->count) = node;
		list->count++;
		ret = 1;
	} else if (index >= 0 && index < list->count) {
		for (i = list->count; i > index; i--) {
			*(list->nodes + i) = *(list->nodes + i - 1);
		}
		*(list->nodes + index) = node;
		list->count++;
		ret = 1;
	}

	return ret;
}


static struct YListNode *_array_list_remove(struct YArrayList *list, struct YListNode *node)
{
	if (list == NULL || node == NULL)
		return NULL;

	return YArrayListRemoveAt(list, _array_list_get_index(list, node));
}


struct YListNode *YArrayListRemoveAt(struct YArrayList *list, long index)
{
	struct YListNode *ret = NULL;
	if (list == NULL)
		return ret;

	if (index < 0 || index >= list->count)
		return ret;

	long i;
	ret = YArrayListAt(list, index);
	for (i = index; i < list->count - 1; i++) {
		*(list->nodes + i) = *(list->nodes + i + 1);
	}
	*(list->nodes + list->count - 1) = NULL;
	list->count--;

	return ret;
}


long YArrayListGetCount(struct YArrayList *list)
{
	if (list == NULL)
		return -1;

	return list->count;
}
