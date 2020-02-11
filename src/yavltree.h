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

void YAVLTreeInsert(struct YAVLTree *tree, void *data, USERDATA_DESTROYER destroyer);
void YAVLTreeRemove(struct YAVLTree *tree, void *data);
struct YTreeNode *YAVLTreeFind(struct YAVLTree *tree, void *data);




#ifdef __cplusplus
}
#endif

#endif
