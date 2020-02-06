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


#ifdef __cplusplus
}
#endif

#endif
