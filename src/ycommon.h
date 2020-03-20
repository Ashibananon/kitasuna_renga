/*
 * Kitasuna Renga
 *
 * YCommon Header File
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


#ifndef _Y_COMMON_H_
#define _Y_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function type which releases user data.
 */
typedef void (*USERDATA_DESTROYER)(void *data);

/*
 * Function type which compares user datas.
 */
typedef int (*USERDATA_COMPARER)(void *a, void *b);


/*
 * Y List Node
 */
struct YListNode {
	void *data;
	struct YListNode *pre;
	struct YListNode *next;
	USERDATA_DESTROYER destroyer;
};

/*
 * Allocates a new Y List Node.
 * Returns pointer to the node, or NULL if failed.
 */
struct YListNode *YListNodeNew(void);

/*
 * Allocates a new Y List Node with initial values for
 * user data and user data destroyer.
 * Returns pointer to the node, or NULL if failed.
 */
struct YListNode *YListNodeNewWithData(void *d, USERDATA_DESTROYER destroyer);

/*
 * Release the given Y List Node.
 */
void YListNodeDelete(struct YListNode *node);

/*
 * Release the given Y List Node with user data.
 */
void YListNodeDeleteWithData(struct YListNode *node);


/*
 * Y List Node getter and setter for user data.
 */
void *YListNodeGetData(struct YListNode *node);
void YListNodeSetData(struct YListNode *node, void *d);

/*
 * Y List Node getter and setter for user data destroyer.
 */
void YListNodeSetDestroyer(struct YListNode *node, USERDATA_DESTROYER destroyer);
USERDATA_DESTROYER YListNodeGetDestroyer(struct YListNode *node);


/*
 * Y Tree Node
 */
struct YTreeNode {
	void *data;
	struct YTreeNode *parent;
	struct YTreeNode *lchild;
	struct YTreeNode *rchild;
	USERDATA_DESTROYER destroyer;
	long height;
};

/*
 * Allocates a new Y Tree Node.
 * Returns pointer to the node, or NULL if failed.
 */
struct YTreeNode *YTreeNodeNew(void);

/*
 * Allocates a new Y Tree Node with initial values for
 * user data and user data destroyer.
 * Returns pointer to the node, or NULL if failed.
 */
struct YTreeNode *YTreeNodeNewWithData(void *d, USERDATA_DESTROYER destroyer);

/*
 * Release the given Y Tree Node.
 */
void YTreeNodeDelete(struct YTreeNode *node);

/*
 * Release the given Y Tree Node with user data.
 */
void YTreeNodeDeleteWithData(struct YTreeNode *node);

/*
 * Y Tree Node getter and setter for user data.
 */
void YTreeNodeSetData(struct YTreeNode *node, void *d);
void *YTreeNodeGetData(struct YTreeNode *node);

/*
 * Y Tree Node getter and setter for user data destroyer.
 */
void YTreeNodeSetDestroyer(struct YTreeNode *node, USERDATA_DESTROYER destroyer);
USERDATA_DESTROYER YTreeNodeGetDestroyer(struct YTreeNode *node);

/*
 * Y Tree Node getter for the height of the given node.
 */
long YTreeNodeGetHeight(struct YTreeNode *node);

/*
 * Y Tree Node getter for the parent of the given node.
 */
struct YTreeNode *YTreeNodeGetParent(struct YTreeNode *node);

/*
 * Y Tree Node getter for the left child of the given node.
 */
struct YTreeNode *YTreeNodeGetLeftChild(struct YTreeNode *node);

/*
 * Y Tree Node getter for the right child of the given node.
 */
struct YTreeNode *YTreeNodeGetRightChild(struct YTreeNode *node);

#ifdef __cplusplus
}
#endif

#endif
