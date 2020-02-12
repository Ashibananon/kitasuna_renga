/*
 * Main source
 *
 * Copyright(C) 2020 Ashibananon(Yuan).
 *
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with This program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */


#include <stdio.h>
#include <stdlib.h>

#include "ylinkedlist.h"
#include "yarraylist.h"
#include "yavltree.h"
#include "ystack.h"

int cmper(void *a, void *b)
{
	return (int)(*((int *)a) - *((int *)b));
}

int main()
{
	int i;
	int *p;
	struct YLinkedList list;
	YLinkedListInit(&list);

	struct YArrayList alist;
	YArrayListInit(&alist);
	YArrayListDestroy(&alist);

	struct YAVLTree tree;
	YAVLTreeInit(&tree);
	YAVLTreeSetDataComparer(&tree, cmper);

	/*
	for (i = 100; i > 0; i--) {
		p = (int *)malloc(sizeof(int));
		*p = i;
		YAVLTreeInsert(&tree, p, free);
	}*/
	p = (int *)malloc(sizeof(int));
	*p = 1;
	YAVLTreeInsert(&tree, p, free);

	p = (int *)malloc(sizeof(int));
	*p = 2;
	YAVLTreeInsert(&tree, p, free);

	p = (int *)malloc(sizeof(int));
	*p = 3;
	YAVLTreeInsert(&tree, p, free);

	p = (int *)malloc(sizeof(int));
	*p = 5;
	YAVLTreeInsert(&tree, p, free);

	p = (int *)malloc(sizeof(int));
	*p = 7;
	YAVLTreeInsert(&tree, p, free);

	p = (int *)malloc(sizeof(int));
	*p = 8;
	YAVLTreeInsert(&tree, p, free);


	struct YTreeNode *tmp = tree.root;
	struct YListNode *ln;
	YLinkedListAppendTail(&list, YListNodeNewWithData(tmp, NULL));
	printf("Height: %ld\n", YTreeNodeGetHeight(tmp));
	while (YLinkedListGetCount(&list) > 0) {
		ln = YLinkedListRemoveNode(&list, YLinkedListGetHead(&list));
		if (ln == NULL)
			continue;
		struct YTreeNode *v = ln->data;

		printf("%d", *((int *)v->data));
		if (v->parent != NULL) {
			printf(" parent=%d", *((int *)v->parent->data));
		}
		if (v->lchild != NULL) {
			YLinkedListAppendTail(&list, YListNodeNewWithData(v->lchild, NULL));
			printf(" lchild=%d", *((int *)v->lchild->data));
		}
		if (v->rchild != NULL) {
			YLinkedListAppendTail(&list, YListNodeNewWithData(v->rchild, NULL));
			printf(" rchild=%d", *((int *)v->rchild->data));
		}
		printf("\n");

		YListNodeDelete(ln);
	}


	YAVLTreeDestroy(&tree);
	YLinkedListDestroy(&list);


	return 0;
}
