#include <stdio.h>
#include "list.h"

namespace List
{
Node* PushFront (Node *list, int data)
{
	Node *node = new Node;
	node->data = data;
	node->next = list;
	return node;
}

void Print (Node *list)
{
	if (!list)
	{
		printf ("<empty list>\n");
		return;
	}
	Node *loop_start;
	unsigned int loop_length;
	FindLoop(list, &loop_start, &loop_length);
	while (list != loop_start)
	{
		printf ("%d ", list->data);
		list = list->next;
	}
	if (loop_start)
	{
		printf ("| ");
		for (unsigned int i = 0; i < loop_length; i++)
		{
			printf ("%d ", list->data);
			list = list->next;
		}
		printf ("|\n");
	}
	else
		printf ("\n");
}

Node* Reverse (Node *list)
{
	Node *prev = nullptr, *cur;
	while (list)
	{
		cur = list;
		list = list->next;
		cur->next = prev;
		prev = cur;
	}
	list = prev;
	return list;
}

bool FindLoop (Node *list, Node **loop_start, unsigned int *loop_length)
{
	if (!list)
		return false;
	Node *slow_iter = list, *fast_iter = list;
	unsigned int slow_iter_movements = 0;
	while (true)
	{
		if (fast_iter->next && fast_iter->next->next)
			fast_iter = fast_iter->next->next;
		else
		{
			if (loop_start)
				*loop_start = nullptr;
			if (loop_length)
				*loop_length = 0;
			return false;
		}
		// if we can move fast_iter, than we can move slow_iter without any checks
		slow_iter = slow_iter->next;
		slow_iter_movements++;
		if (slow_iter == fast_iter)
			break;
	}
	// found loop
	if (loop_length)
		*loop_length = slow_iter_movements;
	fast_iter = list;
	while (slow_iter != fast_iter)
	{
		slow_iter = slow_iter->next;
		fast_iter = fast_iter->next;
	}
	if (loop_start)
		*loop_start = fast_iter;
	return true;
}

Node* Clear (Node *list)
{
	Node *loop_start;
	FindLoop(list, &loop_start, nullptr);
	Node *temp;
	while (list != loop_start)
	{
		temp = list;
		list = list->next;
		delete temp;
	}
	return nullptr;
}
}
