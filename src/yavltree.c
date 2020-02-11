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
		}

		YStackDelete(stack);
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


static void insert_node(struct YAVLTree *tree,
			struct _node_path *path,
			void *data,
			USERDATA_DESTROYER destroyer)
{
	struct YTreeNode *pos;
	enum _path_direction direction;

	/* Insert data */
	struct YTreeNode *node = YTreeNodeNewWithData(data, destroyer);
	if (node == NULL)
		return;

	pos = path->prev;
	direction = path->direction;
	if (pos == NULL && direction == _pd_self) {
		tree->root = node;
		tree->count++;
		return;
	}

	if (direction == _pd_left) {
		pos->lchild = node;
		node->parent = pos;
		tree->count++;
	} else if (direction == _pd_right) {
		pos->rchild = node;
		node->parent = pos;
		tree->count++;
	} else {
		goto dire_err;
	}

	pos->height = max_height(pos->lchild, pos->rchild) + 1;

	/* Balance tree */
	long h1;
	long h2;
	long bf;
	struct YTreeNode *tmp = tree->root;
	while (pos != NULL) {
		h1 = YTreeNodeGetHeight(pos->lchild);
		h2 = YTreeNodeGetHeight(pos->rchild);
		bf = h1 - h2;
		if (bf > 1) {
			if (tree->comparer(data, YTreeNodeGetData(pos->lchild)) < 0) {
				tmp = right_rotate(pos);
			} else {
				left_rotate(pos->lchild);
				tmp = right_rotate(pos);
			}
		} else if (bf < -1) {
			if (tree->comparer(data, YTreeNodeGetData(pos->rchild)) > 0) {
				tmp = left_rotate(pos);
			} else {
				right_rotate(pos->rchild);
				tmp = left_rotate(pos);
			}
		}
		pos = tmp->parent;
	}
	tree->root = tmp;

	return;

dire_err:
	YTreeNodeDelete(node);
	return;
}


void YAVLTreeInsert(struct YAVLTree *tree, void *data, USERDATA_DESTROYER destroyer)
{
	if (tree == NULL || data == NULL)
		return;

	if (tree->comparer == NULL)
		return;

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

	insert_node(tree, &path, data, destroyer);

done:
	return;
}
