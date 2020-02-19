/*
 * Kitasuna Renga
 *
 * YAVLTree Source File
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

#include "ystack.h"
#include "yavltree.h"

void YAVLTreeInit(struct YAVLTree *tree)
{
	if (tree != NULL) {
		tree->root = NULL;
		tree->comparer = 0;
		tree->count = 0;
	}
}


void YAVLTreeInitWithData(struct YAVLTree *tree, USERDATA_COMPARER cmp)
{
	if (tree != NULL) {
		tree->root = NULL;
		tree->comparer = cmp;
		tree->count = 0;
	}
}


void YAVLTreeDestroy(struct YAVLTree *tree)
{
	if (tree != NULL) {
		if (tree->root == NULL)
			return;

		struct YTreeNode *tnode;
		struct YStack *stack = YStackNew();
		YStackPush(stack, tree->root);
		while (YStackGetCount(stack) > 0) {
			tnode = (struct YTreeNode *)YStackPop(stack);

			if (tnode->lchild != NULL)
				YStackPush(stack, tnode->lchild);
			if (tnode->rchild != NULL)
				YStackPush(stack, tnode->rchild);

			YTreeNodeDelete(tnode);
			tree->count--;
		}

		YStackDelete(stack);

		tree->root = NULL;
		tree->comparer = NULL;
	}
}


struct YAVLTree *YAVLTreeNew(void)
{
	struct YAVLTree *tree = (struct YAVLTree *)malloc(sizeof(struct YAVLTree));
	if (tree != NULL)
		YAVLTreeInit(tree);

	return tree;
}


struct YAVLTree *YAVLTreeNewWithData(USERDATA_COMPARER cmp)
{
	struct YAVLTree *tree = (struct YAVLTree *)malloc(sizeof(struct YAVLTree));
	if (tree != NULL)
		YAVLTreeInitWithData(tree, cmp);

	return tree;
}


void YAVLTreeDelete(struct YAVLTree *tree)
{
	if (tree != NULL) {
		YAVLTreeDestroy(tree);
		free(tree);
	}
}


void YAVLTreeSetDataComparer(struct YAVLTree *tree, USERDATA_COMPARER cmp)
{
	if (tree != NULL)
		tree->comparer = cmp;
}


USERDATA_COMPARER YAVLTreeGetDataComparer(struct YAVLTree *tree)
{
	USERDATA_COMPARER ret = NULL;
	if (tree != NULL)
		ret = tree->comparer;

	return ret;
}


long YAVLTreeGetCount(struct YAVLTree *tree)
{
	long ret = -1;
	if (tree != NULL)
		ret = tree->count;

	return ret;
}


static long max_height(struct YTreeNode *n1, struct YTreeNode *n2)
{
	long h1 = YTreeNodeGetHeight(n1);
	long h2 = YTreeNodeGetHeight(n2);
	if (h1 > h2)
		return h1;
	else
		return h2;
}


static long get_balance_factor(struct YTreeNode *node)
{
	if (node == NULL)
		return 0;
	else
		return (YTreeNodeGetHeight(node->lchild)
			- YTreeNodeGetHeight(node->rchild));
}


static struct YTreeNode *left_rotate(struct YTreeNode *node)
{
	if (node == NULL)
		return NULL;

	struct YTreeNode *parent = node->parent;
	struct YTreeNode *lc = node->lchild;
	struct YTreeNode *rc = node->rchild;
	if (rc != NULL) {
		node->rchild = rc->lchild;
		if (rc->lchild != NULL)
			rc->lchild->parent = node;

		node->parent = rc;
		rc->lchild = node;

		rc->parent = parent;
		if (parent != NULL) {
			if (parent->lchild == node)
				parent->lchild = rc;
			else if (parent->rchild == node)
				parent->rchild = rc;
		}

		node->height = max_height(lc, node->rchild) + 1;
		rc->height = max_height(node, rc->rchild) + 1;

		return rc;
	} else {
		return node;
	}
}


static struct YTreeNode *right_rotate(struct YTreeNode *node)
{
	if (node == NULL)
		return NULL;

	struct YTreeNode *parent = node->parent;
	struct YTreeNode *lc = node->lchild;
	struct YTreeNode *rc = node->rchild;
	if (lc != NULL) {
		node->lchild = lc->rchild;
		if (lc->rchild != NULL)
			lc->rchild->parent = node;

		node->parent = lc;
		lc->rchild = node;

		lc->parent = parent;
		if (parent != NULL) {
			if (parent->lchild == node)
				parent->lchild = lc;
			else if (parent->rchild == node)
				parent->rchild = lc;
		}

		node->height = max_height(node->lchild, rc) + 1;
		lc->height = max_height(lc->lchild, node) + 1;

		return lc;
	} else {
		return node;
	}
}


enum _path_direction {
	_pd_self,
	_pd_left,
	_pd_right
};

struct _node_path {
	struct YTreeNode *prev;
	enum _path_direction direction;
};


static int insert_node(struct YAVLTree *tree,
			struct _node_path *path,
			void *data,
			USERDATA_DESTROYER destroyer)
{
	int ret = 0;
	struct YTreeNode *pos;
	enum _path_direction direction;

	/* Insert data */
	struct YTreeNode *node = YTreeNodeNewWithData(data, destroyer);
	if (node == NULL)
		return 0;

	pos = path->prev;
	direction = path->direction;
	if (pos == NULL && direction == _pd_self) {
		tree->root = node;
		tree->count++;
		return 1;
	}

	if (direction == _pd_left) {
		pos->lchild = node;
		node->parent = pos;
		tree->count++;
		ret = 1;
	} else if (direction == _pd_right) {
		pos->rchild = node;
		node->parent = pos;
		tree->count++;
		ret = 1;
	} else {
		goto dire_err;
	}

	/* Balance tree */
	long bf;
	struct YTreeNode *tmp = tree->root;
	while (pos != NULL) {
		pos->height = max_height(pos->lchild, pos->rchild) + 1;
		bf = get_balance_factor(pos);
		if (bf > 1) {
			if (get_balance_factor(pos->lchild) >= 0) {
				tmp = right_rotate(pos);
			} else {
				left_rotate(pos->lchild);
				tmp = right_rotate(pos);
			}
		} else if (bf < -1) {
			if (get_balance_factor(pos->rchild) <= 0) {
				tmp = left_rotate(pos);
			} else {
				right_rotate(pos->rchild);
				tmp = left_rotate(pos);
			}
		} else {
			tmp = pos;
		}
		pos = tmp->parent;
	}
	tree->root = tmp;

	return ret;

dire_err:
	YTreeNodeDelete(node);
	return ret;
}


int YAVLTreeInsert(struct YAVLTree *tree, void *data, USERDATA_DESTROYER destroyer)
{
	int ret = 0;
	if (tree == NULL || data == NULL || tree->comparer == NULL)
		return ret;

	int cmp_result;
	struct _node_path path;
	path.prev = NULL;
	path.direction = _pd_self;

	struct YTreeNode *pos = tree->root;
	while (pos != NULL) {
		path.prev = pos;
		cmp_result = tree->comparer(pos->data, data);
		if (cmp_result < 0) {
			/* Go on with right subtree */
			pos = pos->rchild;
			path.direction = _pd_right;
		} else if (cmp_result > 0) {
			/* Go on with left subtree */
			pos = pos->lchild;
			path.direction = _pd_left;
		} else {
			/* data already in the tree, return */
			goto done;
		}
	}

	ret = insert_node(tree, &path, data, destroyer);

done:
	return ret;
}


struct YTreeNode *YAVLTreeFind(struct YAVLTree *tree, void *data)
{
	struct YTreeNode *ret = NULL;
	struct YTreeNode *cur;
	if (tree == NULL || data == NULL || tree->comparer == NULL)
		return ret;

	cur = tree->root;
	int cmp_result;
	while (cur != NULL) {
		cmp_result = tree->comparer(cur->data, data);
		if (cmp_result > 0) {
			cur = cur->lchild;
		} else if (cmp_result < 0) {
			cur = cur->rchild;
		} else {
			ret = cur;
			break;
		}
	}

	return ret;
}


static struct YTreeNode *get_prev_node(struct YTreeNode *node)
{
	struct YTreeNode *ret = NULL;
	struct YTreeNode *cur;
	struct YTreeNode *pnt;
	if (node == NULL)
		return ret;

	if (node->lchild != NULL) {
		cur = node->lchild;
		while (cur != NULL) {
			ret = cur;
			cur = cur->rchild;
		}
	} else {
		cur = node;
		pnt = cur->parent;
		while (pnt != NULL) {
			if (pnt->rchild == cur) {
				ret = pnt;
				break;
			}
			cur = pnt;
			pnt = pnt->parent;
		}
	}

	return ret;
}


static struct YTreeNode *get_next_node(struct YTreeNode *node)
{
	struct YTreeNode *ret = NULL;
	struct YTreeNode *cur;
	struct YTreeNode *pnt;
	if (node == NULL)
		return ret;

	if (node->rchild != NULL) {
		cur = node->rchild;
		while (cur != NULL) {
			ret = cur;
			cur = cur->lchild;
		}
	} else {
		cur = node;
		pnt = cur->parent;
		while (pnt != NULL) {
			if (pnt->lchild == cur) {
				ret = pnt;
				break;
			}
			cur = pnt;
			pnt = pnt->parent;
		}
	}

	return ret;
}


struct YTreeNode *YAVLTreeGetMinimum(struct YAVLTree *tree)
{
	struct YTreeNode *ret = NULL;
	struct YTreeNode *cur;
	if (tree == NULL)
		return ret;

	cur = tree->root;
	while (cur != NULL) {
		ret = cur;
		cur = cur->lchild;
	}

	return ret;
}


struct YTreeNode *YAVLTreeGetMaximum(struct YAVLTree *tree)
{
	struct YTreeNode *ret = NULL;
	struct YTreeNode *cur;
	if (tree == NULL)
		return ret;

	cur = tree->root;
	while (cur != NULL) {
		ret = cur;
		cur = cur->rchild;
	}

	return ret;
}


struct YTreeNode *YAVLTreeGetPrevious(struct YTreeNode *node)
{
	return get_prev_node(node);
}


struct YTreeNode *YAVLTreeGetNext(struct YTreeNode *node)
{
	return get_next_node(node);
}


struct YTreeNode *YAVLTreeRemove(struct YAVLTree *tree, struct YTreeNode *node)
{
	struct YTreeNode *ret = NULL;
	struct YTreeNode *cur;
	struct YTreeNode *tmp;
	struct YTreeNode *pnt;
	void *d;
	if (tree == NULL || node == NULL || tree->comparer == NULL)
		return ret;

	if (tree->root == NULL)
		return ret;

	if (tree->count == 1) {
		if (tree->root == node) {
			tree->root = NULL;
			tree->count--;
			ret = node;
		}
	} else {
		cur = node;
		pnt = cur->parent;
		if (cur->lchild == NULL && cur->rchild == NULL) {
			if (pnt->lchild == cur) {
				pnt->lchild = NULL;
			} else if (pnt->rchild == cur) {
				pnt->rchild = NULL;
			} else {
				/* Error! */
				goto child_err;
			}
			cur->parent = NULL;
			tree->count--;
			ret = cur;
			cur = pnt;
		} else if (cur->lchild == NULL && cur->rchild != NULL) {
			tmp = cur->rchild;

			d = cur->data;
			cur->data = tmp->data;
			tmp->data = d;

			cur->rchild = NULL;
			tmp->parent = NULL;
			tree->count--;
			ret = tmp;
		} else if (cur ->lchild != NULL && cur->rchild == NULL) {
			tmp = cur->lchild;

			d = cur->data;
			cur->data = tmp->data;
			tmp->data = d;

			cur->lchild = NULL;
			tmp->parent = NULL;
			tree->count--;
			ret = tmp;
		} else {
			tmp = get_next_node(cur);

			d = cur->data;
			cur->data = tmp->data;
			tmp->data = d;

			if (tmp->rchild != NULL) {
				d = tmp->data;
				tmp->data = tmp->rchild->data;
				tmp->rchild->data = d;
				tmp = tmp->rchild;
			}
			pnt = tmp->parent;
			if (pnt->lchild == tmp) {
				pnt->lchild = NULL;
			} else if (pnt->rchild == tmp) {
				pnt->rchild = NULL;
			} else {
				/* Error */
				goto child_err;
			}
			tmp->parent = NULL;
			tree->count--;
			ret = tmp;
			cur = pnt;
		}

		/* Balance tree */
		long bf;
		tmp = tree->root;
		while (cur != NULL) {
			cur->height = max_height(cur->lchild, cur->rchild) + 1;
			bf = get_balance_factor(cur);
			if (bf < -1) {
				if (get_balance_factor(cur->rchild) <= 0) {
					tmp = left_rotate(cur);
				} else {
					right_rotate(cur->rchild);
					tmp = left_rotate(cur);
				}
			} else if (bf > 1) {
				if (get_balance_factor(cur->lchild) >= 0) {
					tmp = right_rotate(cur);
				} else {
					left_rotate(cur->lchild);
					tmp = right_rotate(cur);
				}
			} else {
				tmp = cur;
			}
			cur = cur->parent;
		}
		tree->root = tmp;
	}

child_err:
	return ret;
}
