#include <stdio.h>
#include <time.h>
#include "list.h"

void insert_front()
{
	List* list;
	clock_t time = clock();

	initialize(&list);

	for (int i = 0; i < 100000; i++)
	{
		insert(list, 0, i);
	}

	time = clock() - time;

	printf("front:  %6d\n", time);

	dispose(&list);
}

void insert_back()
{
	List* list;
	clock_t time = clock();

	initialize(&list);

	for (int i = 0; i < 100000; i++)
	{
		insert(list, i, i);
	}

	time = clock() - time;

	printf("back:   %6d\n", time);

	dispose(&list);
}

void insert_middle()
{
	List* list;
	clock_t time = clock();

	initialize(&list);

	for (int i = 0; i < 100000; i++)
	{
		insert(list, i / 2, i);
	}

	time = clock() - time;

	printf("middle: %6d\n", time);

	dispose(&list);
}

int main()
{
	for (int i = 0; i < 3; i++)
	{
		insert_front();
		insert_back();
		insert_middle();
	}
}