#include "list.h"

int main()
{
	List* list;
	initialize(&list);

	insert(list, 0, 0);
	insert(list, 0, 1);
	insert(list, 0, 2);
	insert(list, 0, 3);
	insert(list, 0, 4);
	insert(list, 0, 5);
	insert(list, 0, 6);
	insert(list, 6, 7);

	remove(list, 2);

	dispose(&list);
}