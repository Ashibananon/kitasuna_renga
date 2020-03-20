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

/*
 * Y Stack
 */
struct YStack {
	struct YLinkedList stack;
};

/*
 * Initialize the stack.
 */
void YStackInit(struct YStack *s);

/*
 * Destroy the stack.
 */
void YStackDestroy(struct YStack *s);

/*
 * Allocate a new stack.
 * Returns pointer to the stack, or NULL if failed.
 */
struct YStack *YStackNew(void);

/*
 * Release the given stack.
 */
void YStackDelete(struct YStack *s);

/*
 * Push the given data to stack.
 */
void YStackPush(struct YStack *s, void *data, USERDATA_DESTROYER destroyer);

/*
 * Pop from stack.
 * Returns the data that poped.
 */
void *YStackPop(struct YStack *s);

/*
 * Returns count of the given stack.
 */
long YStackGetCount(struct YStack *s);


#ifdef __cplusplus
}
#endif

#endif // YSTACK_H
