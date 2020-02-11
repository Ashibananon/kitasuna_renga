#include <stdlib.h>

#include "ycommon.h"
#include "ystack.h"

void YStackInit(struct YStack *s)
{
	if (s != NULL)
		YLinkedListInit(&s->stack);
}


void YStackDestroy(struct YStack *s)
{
	if (s != NULL)
		YLinkedListDestroy(&s->stack);
}


struct YStack *YStackNew(void)
{
	struct YStack *s = (struct YStack *)malloc(sizeof(struct YStack));
	if (s != NULL)
		YStackInit(s);

	return s;
}


void YStackDelete(struct YStack *s)
{
	if (s != NULL) {
		YStackDestroy(s);
		free(s);
	}
}


void YStackPush(struct YStack *s, void *data)
{
	if (s != NULL)
		YLinkedListAppendTail(&s->stack, YListNodeNewWithData(data, NULL));
}


void *YStackPop(struct YStack *s)
{
	void *ret = NULL;
	if (s != NULL) {
		struct YListNode *tail =
			YLinkedListRemoveNode(&s->stack,
					      YLinkedListGetTail(&s->stack));

		if (tail != NULL)
			ret = tail->data;

		YListNodeDelete(tail);
	}

	return ret;
}


long YStackGetCount(struct YStack *s)
{
	long ret = -1;
	if (s != NULL)
		ret = YLinkedListGetCount(&s->stack);

	return ret;
}
