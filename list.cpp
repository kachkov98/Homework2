#include <stdio.h>
#include <assert.h>
#include <new>
#include "list.h"

namespace List
{
void PushFront (Node **list, int data)
{
	Node *node = new (std::nothrow) Node;
	assert (node);
	node->data = data;
	node->next = *list;
	*list = node;
}

void Print (const Node *list)
{
	if (!list)
		printf ("<empty list>\n");
	else
	{
		while (list)
		{
			printf ("%d ", list->data);
			list = list->next;
		}
		printf ("\n");
	}
}

void Reverse (Node **list)
{
	Node *prev = nullptr, *cur;
	while (*list)
	{
		cur = *list;
		*list = (*list)->next;
		cur->next = prev;
		prev = cur;
	}
	*list = prev;
}

void Clear (Node **list)
{
	Node *temp;
	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		delete temp;
	}
}
}
