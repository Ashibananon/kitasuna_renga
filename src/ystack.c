/*
 * Kitasuna Renga
 *
 * YStack Source File
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
