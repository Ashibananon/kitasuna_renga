#ifndef _Y_COMMON_H_
#define _Y_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*USERDATA_DESTROYER)(void *data);

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

struct YListNode *YListNodeNew(void);
struct YListNode *YListNodeNewWithData(void *d, USERDATA_DESTROYER destroyer);
void YListNodeDelete(struct YListNode *node);

void *YListNodeGetData(struct YListNode *node);
void YListNodeSetData(struct YListNode *node, void *d);
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

struct YTreeNode *YTreeNodeNew(void);
struct YTreeNode *YTreeNodeNewWithData(void *d, USERDATA_DESTROYER destroyer);
void YTreeNodeDelete(struct YTreeNode *node);

void YTreeNodeSetData(struct YTreeNode *node, void *d);
void *YTreeNodeGetData(struct YTreeNode *node);
void YTreeNodeSetDestroyer(struct YTreeNode *node, USERDATA_DESTROYER destroyer);
USERDATA_DESTROYER YTreeNodeGetDestroyer(struct YTreeNode *node);

long YTreeNodeGetHeight(struct YTreeNode *node);
struct YTreeNode *YTreeNodeGetParent(struct YTreeNode *node);
struct YTreeNode *YTreeNodeGetLeftChild(struct YTreeNode *node);
struct YTreeNode *YTreeNodeGetRightChild(struct YTreeNode *node);

#ifdef __cplusplus
}
#endif

#endif
