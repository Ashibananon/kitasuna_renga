#ifndef _Y_STACK_H_
#define _Y_STACK_H_

#include "ylinkedlist.h"

#ifdef __cplusplus
extern "C" {
#endif

struct YStack {
	struct YLinkedList stack;
};

void YStackInit(struct YStack *s);
void YStackDestroy(struct YStack *s);
struct YStack *YStackNew(void);
void YStackDelete(struct YStack *s);

void YStackPush(struct YStack *s, void *data);
void *YStackPop(struct YStack *s);
long YStackGetCount(struct YStack *s);


#ifdef __cplusplus
}
#endif

#endif // YSTACK_H
