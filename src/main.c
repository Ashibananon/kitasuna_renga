#include <stdio.h>

#include "ylinkedlist.h"
#include "yarraylist.h"

int main()
{
	struct YLinkedList list;
	YLinkedListInit(&list);
	YLinkedListDestroy(&list);

	struct YArrayList alist;
	YArrayListInit(&alist);
	YArrayListDestroy(&alist);

	return 0;
}
