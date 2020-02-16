/*
 * Kitasuna Renga
 *
 * YAVLTree Header File
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


#ifndef _Y_AVLTREE_H
#define _Y_AVLTREE_H

#include "ycommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Y AVL Tree
 */
struct YAVLTree {
	struct YTreeNode *root;
	USERDATA_COMPARER comparer;
	long count;
};

/*
 * Init the given avl tree.
 */
void YAVLTreeInit(struct YAVLTree *tree);

/*
 * Init the given avl tree with user data comparer.
 */
void YAVLTreeInitWithData(struct YAVLTree *tree, USERDATA_COMPARER cmp);

/*
 * Destroy the given avl tree.
 */
void YAVLTreeDestroy(struct YAVLTree *tree);

/*
 * Allocate a new avl tree.
 * Returns pointer to the tree, or NULL if failed.
 */
struct YAVLTree *YAVLTreeNew(void);

/*
 * Allocate a new avl tree with user data comparer.
 * Returns pointer to the tree, or NULL if failed.
 */
struct YAVLTree *YAVLTreeNewWithData(USERDATA_COMPARER cmp);

/*
 * Release the given avl tree.
 */
void YAVLTreeDelete(struct YAVLTree *tree);

/*
 * AVL tree getter and setter for user data comparer.
 */
void YAVLTreeSetDataComparer(struct YAVLTree *tree, USERDATA_COMPARER cmp);
USERDATA_COMPARER YAVLTreeGetDataComparer(struct YAVLTree *tree);

/*
 * Returns count of the given tree.
 */
long YAVLTreeGetCount(struct YAVLTree *tree);

/*
 * Insert to the tree with given data and data destroyer.
 * Returns 1 if insertion succeeded.
 */
int YAVLTreeInsert(struct YAVLTree *tree, void *data, USERDATA_DESTROYER destroyer);

/*
 * Find from the tree if there is an node with the same data.
 * Returns the tree node if found, or NULL if not found.
 */
struct YTreeNode *YAVLTreeFind(struct YAVLTree *tree, void *data);

/*
 * Returns the tree node that having the minimum value of the tree.
 * If error occurs, NULL is returned.
 */
struct YTreeNode *YAVLTreeGetMinimum(struct YAVLTree *tree);

/*
 * Returns the tree node that having the maximum value of the tree.
 * If error occurs, NULL is returned.
 */
struct YTreeNode *YAVLTreeGetMaximum(struct YAVLTree *tree);

/*
 * Returns the in-order previous tree node of the given node.
 */
struct YTreeNode *YAVLTreeGetPrevious(struct YTreeNode *node);

/*
 * Returns the in-order next tree node of the given node.
 */
struct YTreeNode *YAVLTreeGetNext(struct YTreeNode *node);

/*
 * Remove node from the tree.
 * Returns the removed tree node if success, or NULL if failed.
 */
struct YTreeNode *YAVLTreeRemove(struct YAVLTree *tree, struct YTreeNode *node);


#ifdef __cplusplus
}
#endif

#endif
