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

struct YAVLTree {
	struct YTreeNode *root;
	USERDATA_COMPARER comparer;
	long count;
};

void YAVLTreeInit(struct YAVLTree *tree);
void YAVLTreeInitWithData(struct YAVLTree *tree, USERDATA_COMPARER cmp);
void YAVLTreeDestroy(struct YAVLTree *tree);

struct YAVLTree *YAVLTreeNew(void);
struct YAVLTree *YAVLTreeNewWithData(USERDATA_COMPARER cmp);
void YAVLTreeDelete(struct YAVLTree *tree);

void YAVLTreeSetDataComparer(struct YAVLTree *tree, USERDATA_COMPARER cmp);
USERDATA_COMPARER YAVLTreeGetDataComparer(struct YAVLTree *tree);

long YAVLTreeGetCount(struct YAVLTree *tree);

int YAVLTreeInsert(struct YAVLTree *tree, void *data, USERDATA_DESTROYER destroyer);
struct YTreeNode *YAVLTreeFind(struct YAVLTree *tree, void *data);
struct YTreeNode *YAVLTreeGetMinimum(struct YAVLTree *tree);
struct YTreeNode *YAVLTreeGetMaximum(struct YAVLTree *tree);
struct YTreeNode *YAVLTreeGetPrevious(struct YTreeNode *node);
struct YTreeNode *YAVLTreeGetNext(struct YTreeNode *node);
struct YTreeNode *YAVLTreeRemove(struct YAVLTree *tree, struct YTreeNode *node);


#ifdef __cplusplus
}
#endif

#endif
