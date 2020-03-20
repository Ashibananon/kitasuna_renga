/*
 * Kitasuna Renga
 *
 * YCommon Source File
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
	if (node != NULL)
		free(node);
}


void YListNodeDeleteWithData(struct YListNode *node)
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


/*
 * Y Tree Node implementation
 */
struct YTreeNode *YTreeNodeNew(void)
{
	struct YTreeNode *node = (struct YTreeNode *)malloc(sizeof(struct YTreeNode));
	if (node != NULL) {
		node->data = NULL;
		node->parent = NULL;
		node->lchild = NULL;
		node->rchild = NULL;
		node->destroyer = NULL;
		node->height = 0;
	}

	return node;
}


struct YTreeNode *YTreeNodeNewWithData(void *d, USERDATA_DESTROYER destroyer)
{
	struct YTreeNode *node = (struct YTreeNode *)malloc(sizeof(struct YTreeNode));
	if (node != NULL) {
		node->data = d;
		node->parent = NULL;
		node->lchild = NULL;
		node->rchild = NULL;
		node->destroyer = destroyer;
		node->height = 0;
	}

	return node;
}


void YTreeNodeDelete(struct YTreeNode *node)
{
	if (node != NULL)
		free(node);
}


void YTreeNodeDeleteWithData(struct YTreeNode *node)
{
	if (node != NULL) {
		if (node->destroyer != NULL) {
			node->destroyer(node->data);
			node->data = NULL;
		}

		free(node);
	}
}


void YTreeNodeSetData(struct YTreeNode *node, void *d)
{
	if (node != NULL)
		node->data = d;
}


void *YTreeNodeGetData(struct YTreeNode *node)
{
	void *ret = NULL;
	if (node != NULL)
		ret = node->data;

	return ret;
}


void YTreeNodeSetDestroyer(struct YTreeNode *node, USERDATA_DESTROYER destroyer)
{
	if (node != NULL)
		node->destroyer = destroyer;
}


USERDATA_DESTROYER YTreeNodeGetDestroyer(struct YTreeNode *node)
{
	USERDATA_DESTROYER ret = NULL;
	if (node != NULL)
		ret = node->destroyer;

	return ret;
}


long YTreeNodeGetHeight(struct YTreeNode *node)
{
	long ret = -1;
	if (node != NULL)
		ret = node->height;

	return ret;
}


struct YTreeNode *YTreeNodeGetParent(struct YTreeNode *node)
{
	struct YTreeNode *ret = NULL;
	if (node != NULL)
		ret = node->parent;

	return ret;
}


struct YTreeNode *YTreeNodeGetLeftChild(struct YTreeNode *node)
{
	struct YTreeNode *ret = NULL;
	if (node != NULL)
		ret = node->lchild;

	return ret;
}


struct YTreeNode *YTreeNodeGetRightChild(struct YTreeNode *node)
{
	struct YTreeNode *ret = NULL;
	if (node != NULL)
		ret = node->rchild;

	return ret;
}
