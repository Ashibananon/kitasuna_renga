/*
 * Kitasuna Renga
 *
 * YStack Header File
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
