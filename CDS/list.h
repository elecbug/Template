#pragma once
#include <stdlib.h>

typedef int element;
typedef long long int indexer;

typedef struct node
{
	element data;
	struct node* prev;
	struct node* next;

} Node;

typedef struct list
{
	Node* head;
	Node* tail;
	indexer count;

} List;

void initialize(List** list)
{
	*list = (List*)malloc(sizeof(List));
	
	if (*list != NULL)
	{
		(*list)->head = (Node*)malloc(sizeof(Node));
		(*list)->tail = (Node*)malloc(sizeof(Node));
		(*list)->count = 0;

		if (((*list)->head && (*list)->tail) != NULL)
		{
			(*list)->head->next = (*list)->tail;
			(*list)->tail->prev = (*list)->head;
			(*list)->head->prev = NULL;
			(*list)->tail->next = NULL;
		}
	}
}

Node* node(List* list, indexer index)
{
	if (index < 0 || index > list->count)
	{
		return NULL;
	}

	Node* now;
	
	if (index < list->count / 2)
	{
		now = list->head->next;

		for (int i = 0; i < index; i++)
		{
			now = now->next;
		}
	}
	else
	{
		now = list->tail;

		for (int i = list->count; i > index; i--)
		{
			now = now->prev;
		}
	}

	return now;
}

element* at(List* list, indexer index)
{
	return &(node(list, index)->data);
}

void insert(List* list, indexer index, element value)
{
	Node* loc = node(list, index);
	Node* plus = (Node*)malloc(sizeof(Node));

	if (plus != NULL)
	{
		plus->data = value;
		plus->prev = loc->prev;
		plus->next = loc;

		plus->prev->next = plus;
		plus->next->prev = plus;

		list->count++;
	}
}

void erase(List* list, indexer index)
{
	Node* loc = node(list, index);

	loc->prev->next = loc->next;
	loc->next->prev = loc->prev;
	
	free(loc);

	list->count--;
}

void dispose(List** list)
{
	while ((*list)->count != 0)
	{
		erase(*list, 0);
	}

	free((*list)->head);
	free((*list)->tail);

	free(*list);
}