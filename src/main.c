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

	struct YAVLTree tree;
	YAVLTreeInit(&tree);
	YAVLTreeSetDataComparer(&tree, cmper);


	for (i = 100; i > 0; i--) {
		p = (int *)malloc(sizeof(int));
		*p = i;
		if (YAVLTreeInsert(&tree, p, free) != 1) {
			free(p);
		}
	}
	p = (int *)malloc(sizeof(int));
	*p = 1;
	if (YAVLTreeInsert(&tree, p, free) != 1) {
		free(p);
	}

	p = (int *)malloc(sizeof(int));
	*p = 2;
	if (YAVLTreeInsert(&tree, p, free) != 1) {
		free(p);
	}

	p = (int *)malloc(sizeof(int));
	*p = 3;
	if (YAVLTreeInsert(&tree, p, free) != 1) {
		free(p);
	}

	p = (int *)malloc(sizeof(int));
	*p = 5;
	if (YAVLTreeInsert(&tree, p, free) != 1) {
		free(p);
	}

	p = (int *)malloc(sizeof(int));
	*p = 7;
	if (YAVLTreeInsert(&tree, p, free) != 1) {
		free(p);
	}

	p = (int *)malloc(sizeof(int));
	*p = 8;
	if (YAVLTreeInsert(&tree, p, free) != 1) {
		free(p);
	}

	p = (int *)malloc(sizeof(int));
	*p = 0;
	if (YAVLTreeInsert(&tree, p, free) != 1) {
		free(p);
	}

	p = (int *)malloc(sizeof(int));
	*p = 0;
	if (YAVLTreeInsert(&tree, p, free) != 1) {
		free(p);
	}

	p = (int *)malloc(sizeof(int));
	*p = -1;
	if (YAVLTreeInsert(&tree, p, free) != 1) {
		free(p);
	}

	int pp = 2;
	struct YTreeNode *tnode = YAVLTreeRemove(&tree, YAVLTreeFind(&tree, &pp));
	YTreeNodeDelete(tnode);

	for (i = -1; i < 110; i++) {
		tnode = YAVLTreeRemove(&tree, YAVLTreeFind(&tree, &i));
		YTreeNodeDelete(tnode);

	}
	//pp = -1;
	//tnode = YAVLTreeRemove(&tree, YAVLTreeFind(&tree, &pp));
	//YTreeNodeDelete(tnode);

	struct YTreeNode *min = YAVLTreeGetMinimum(&tree);
	struct YTreeNode *max = YAVLTreeGetMaximum(&tree);
	struct YTreeNode *ccc;
	for (ccc = min; ccc != NULL; ccc = YAVLTreeGetNext(ccc)) {
		printf("%d ", *((int *)YTreeNodeGetData(ccc)));
	}
	printf("\n");

	struct YTreeNode *tmp = tree.root;
	struct YListNode *ln;
	YLinkedListAppendTail(&list, YListNodeNewWithData(tmp, NULL));
	printf("Height: %ld\n", YTreeNodeGetHeight(tmp));
	while (YLinkedListGetCount(&list) > 0) {
		ln = YLinkedListRemoveNode(&list, YLinkedListGetHead(&list));
		if (ln == NULL)
			continue;
		struct YTreeNode *v = ln->data;
		if (v == NULL) {
			YListNodeDelete(ln);
			continue;
		}

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


	for (i = 0; i < 100; i++) {
		int *ttttt = (int *)malloc(sizeof(int));
		*ttttt = i;
		struct YListNode *n = YListNodeNewWithData(ttttt, free);
		YArrayListInsertBeforeIndex(&alist, 0, n);
	}

	struct YListNode *rr = YArrayListRemoveAt(&alist, 1000);
	YListNodeDelete(rr);

	rr = YArrayListRemoveAt(&alist, 10);
	YListNodeDelete(rr);

	rr = YArrayListRemoveAt(&alist, 10);
	YListNodeDelete(rr);
	rr = YArrayListRemoveAt(&alist, 10);
	YListNodeDelete(rr);
	rr = YArrayListRemoveAt(&alist, 10);
	YListNodeDelete(rr);
	rr = YArrayListRemoveAt(&alist, 10);
	YListNodeDelete(rr);
	rr = YArrayListRemoveAt(&alist, 10);
	YListNodeDelete(rr);
	rr = YArrayListRemoveAt(&alist, 10);
	YListNodeDelete(rr);
	rr = YArrayListRemoveAt(&alist, 10);
	YListNodeDelete(rr);

	printf("Before remove:\n");
	for (i = 0; i < YArrayListGetCount(&alist); i++) {
		struct YListNode *t = (struct YListNode *)YArrayListAt(&alist, i);
		printf("%d ", *((int *)t->data));
	}
	printf("\n");

	i = 0;
	while (YArrayListGetCount(&alist) > 0 && i < 50) {
		struct YListNode *pp = YArrayListRemoveAt(&alist, 50);
		YListNodeDelete(pp);
		i++;
	}

	printf("After remove:\n");
	for (i = 0; i < YArrayListGetCount(&alist); i++) {
		struct YListNode *t = (struct YListNode *)YArrayListAt(&alist, i);
		printf("%d ", *((int *)t->data));
	}
	printf("\n");

	YArrayListDestroy(&alist);


	return 0;
}
