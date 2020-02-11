#include <stdio.h>

#include "ylinkedlist.h"
#include "yarraylist.h"
#include "yavltree.h"

int main()
{
	struct YLinkedList list;
	YLinkedListInit(&list);
	YLinkedListDestroy(&list);

	struct YArrayList alist;
	YArrayListInit(&alist);
	YArrayListDestroy(&alist);

	struct YAVLTree tree;
	YAVLTreeInit(&tree);
	YAVLTreeDestroy(&tree);


	return 0;
}
