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
#include <string.h>

#include "ylinkedlist.h"
#include "yarraylist.h"
#include "yavltree.h"
#include "ystack.h"
#include "ymap.h"

int cmper(void *a, void *b)
{
	return (int)(*((int *)a) - *((int *)b));
}


static void TestYLinkedList()
{

}


static void TestYAVLTree()
{
	int *p;
	int i;

	struct YLinkedList list;
	YLinkedListInit(&list);

	struct YAVLTree tree;
	YAVLTreeInit(&tree);
	YAVLTreeSetDataComparer(&tree, cmper);


	for (i = 100; i > 0; i--) {
		p = (int *)malloc(sizeof(int));
		*p = i;
		if (YAVLTreeInsert(&tree, p, free) != 1) {
			//free(p);
		}
	}
	p = (int *)malloc(sizeof(int));
	*p = 1;
	if (YAVLTreeInsert(&tree, p, free) != 1) {
		//free(p);
	}

	p = (int *)malloc(sizeof(int));
	*p = 2;
	if (YAVLTreeInsert(&tree, p, free) != 1) {
		//free(p);
	}

	p = (int *)malloc(sizeof(int));
	*p = 3;
	if (YAVLTreeInsert(&tree, p, free) != 1) {
		//free(p);
	}

	p = (int *)malloc(sizeof(int));
	*p = 5;
	if (YAVLTreeInsert(&tree, p, free) != 1) {
		//free(p);
	}

	p = (int *)malloc(sizeof(int));
	*p = 7;
	if (YAVLTreeInsert(&tree, p, free) != 1) {
		//free(p);
	}

	p = (int *)malloc(sizeof(int));
	*p = 8;
	if (YAVLTreeInsert(&tree, p, free) != 1) {
		//free(p);
	}

	p = (int *)malloc(sizeof(int));
	*p = 0;
	if (YAVLTreeInsert(&tree, p, free) != 1) {
		//free(p);
	}

	p = (int *)malloc(sizeof(int));
	*p = 0;
	if (YAVLTreeInsert(&tree, p, free) != 1) {
		//free(p);
	}

	p = (int *)malloc(sizeof(int));
	*p = -1;
	if (YAVLTreeInsert(&tree, p, free) != 1) {
		//free(p);
	}

	int pp = 2;
	struct YTreeNode *tnode = YAVLTreeRemove(&tree, YAVLTreeFind(&tree, &pp));
	YTreeNodeDeleteWithData(tnode);


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
#if 0
	while (YLinkedListGetCount(&list) > 0) {
		ln = YLinkedListRemoveNode(&list, YLinkedListGetHead(&list));
		if (ln == NULL)
			continue;
		struct YTreeNode *v = ln->data;
		if (v == NULL) {
			YListNodeDeleteWithData(ln);
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

		YListNodeDeleteWithData(ln);
	}
#endif

	YAVLTreeDestroy(&tree);
	YLinkedListDestroy(&list);

}


static void TestYArrayList()
{
	struct YArrayList alist;
	YArrayListInit(&alist);

	int i;

	for (i = 0; i < 100; i++) {
		int *ttttt = (int *)malloc(sizeof(int));
		*ttttt = i;
		struct YListNode *n = YListNodeNewWithData(ttttt, free);
		YArrayListInsertBeforeIndex(&alist, 0, n);
	}

	struct YListNode *rr = YArrayListRemoveAt(&alist, 1000);
	YListNodeDeleteWithData(rr);

	rr = YArrayListRemoveAt(&alist, 10);
	YListNodeDeleteWithData(rr);

	rr = YArrayListRemoveAt(&alist, 10);
	YListNodeDeleteWithData(rr);
	rr = YArrayListRemoveAt(&alist, 10);
	YListNodeDeleteWithData(rr);
	rr = YArrayListRemoveAt(&alist, 10);
	YListNodeDeleteWithData(rr);
	rr = YArrayListRemoveAt(&alist, 10);
	YListNodeDeleteWithData(rr);
	rr = YArrayListRemoveAt(&alist, 10);
	YListNodeDeleteWithData(rr);
	rr = YArrayListRemoveAt(&alist, 10);
	YListNodeDeleteWithData(rr);
	rr = YArrayListRemoveAt(&alist, 10);
	YListNodeDeleteWithData(rr);

	printf("Before remove:\n");
	for (i = 0; i < YArrayListGetCount(&alist); i++) {
		struct YListNode *t = (struct YListNode *)YArrayListAt(&alist, i);
		printf("%d ", *((int *)t->data));
	}
	printf("\n");

	i = 0;
	while (YArrayListGetCount(&alist) > 0 && i < 50) {
		struct YListNode *pp = YArrayListRemoveAt(&alist, 50);
		YListNodeDeleteWithData(pp);
		i++;
	}

	printf("After remove:\n");
	for (i = 0; i < YArrayListGetCount(&alist); i++) {
		struct YListNode *t = (struct YListNode *)YArrayListAt(&alist, i);
		printf("%d ", *((int *)t->data));
	}
	printf("\n");

	YArrayListDestroy(&alist);

}


static void TestYStack()
{
	struct YStack yss;
	YStackInit(&yss);

	int *ssi = (int *)malloc(sizeof(int));
	if (ssi != NULL) {
		*ssi = 1;
		YStackPush(&yss, ssi, free);
	}

	ssi = (int *)malloc(sizeof(int));
	if (ssi != NULL) {
		*ssi = 2;
		YStackPush(&yss, ssi, free);
	}

	int *ssii = (int *)YStackPop(&yss);
	if (ssii != NULL) {
		printf("\n\n*ssii=[%d]\n", *ssii);
		free(ssii);
	}


	YStackDestroy(&yss);
}


int cmp(struct YPair *a, struct YPair *b)
{
	if (a == NULL && b == NULL) {
		return 0;
	} else if (a == NULL && b != NULL) {
		return -1;
	} else if (a != NULL && b == NULL) {
		return 1;
	} else {
		char *sa = (char *)YPairGetKey(a);
		char *sb = (char *)YPairGetKey(b);
		return strcmp(sa, sb);
	}
}

static char *GetNewString(char *v)
{
	if (v == NULL)
		return NULL;

	char *ret = (char *)malloc(strlen(v) + 1);
	if (ret != NULL) {
		strcpy(ret, v);
	}

	return ret;
}

static void PutOldString(char *s)
{
	free(s);
}

static void TestYMap()
{
	struct YMap map;
	YMapInitWithPairComparer(&map, cmp);

	char *sret = NULL;

	YMapSetKeyValue(&map,
			GetNewString("0001"), (USERDATA_DESTROYER)PutOldString,
			GetNewString("AAAA"), (USERDATA_DESTROYER)PutOldString);

	YMapSetKeyValue(&map,
			GetNewString("0002"), (USERDATA_DESTROYER)PutOldString,
			GetNewString("BBBB"), (USERDATA_DESTROYER)PutOldString);

	YMapSetKeyValue(&map,
			GetNewString("0003"), (USERDATA_DESTROYER)PutOldString,
			GetNewString("CCCC"), (USERDATA_DESTROYER)PutOldString);

	sret = (char *)YMapGetKeyValue(&map, "0002");
	if (sret != NULL)
		printf("key[0002]-value[%s]\n", sret);
	else
		printf("key[0002] has not set to map.\n");

	YMapRemoveKeyValue(&map, "0002");
	sret = (char *)YMapGetKeyValue(&map, "0002");
	if (sret != NULL)
		printf("key[0002]-value[%s]\n", sret);
	else
		printf("key[0002] has not set to map.\n");

	YMapSetKeyValue(&map,
			GetNewString("0003"), (USERDATA_DESTROYER)PutOldString,
			GetNewString("CCCC"), (USERDATA_DESTROYER)PutOldString);
	sret = (char *)YMapGetKeyValue(&map, "0003");
	if (sret != NULL)
		printf("key[0003]-value[%s]\n", sret);
	else
		printf("key[0003] has not set to map.\n");

	YMapSetKeyValue(&map,
			GetNewString("0003"), (USERDATA_DESTROYER)PutOldString,
			GetNewString("3333"), (USERDATA_DESTROYER)PutOldString);
	sret = (char *)YMapGetKeyValue(&map, "0003");
	if (sret != NULL)
		printf("key[0003]-value[%s]\n", sret);
	else
		printf("key[0003] has not set to map.\n");

	YMapDestroy(&map);
}

int main()
{

	TestYLinkedList();

	TestYAVLTree();

	TestYArrayList();

	TestYStack();

	TestYMap();

	return 0;
}
