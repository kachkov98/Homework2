#include <random>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "tagged_pointer.h"

namespace List
{
	inline namespace V1
	{
		Node* GenerateList(unsigned int nodes_number, int min_val, int max_val)
		{
			std::uniform_int_distribution<int>distribution(min_val, max_val);
			std::random_device generator;
			Node *list = nullptr;
			for (unsigned int i = 0; i < nodes_number; i++)
				list = PushFront(list, distribution(generator));
			return list;
		}

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
			for (;;)
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
			fast_iter = list;
			while (slow_iter != fast_iter)
			{
				slow_iter = slow_iter->next;
				fast_iter = fast_iter->next;
			}
			if (loop_start)
				*loop_start = fast_iter;
			if (loop_length)
			{
				*loop_length = 1;
				while (slow_iter->next != fast_iter)
				{
					(*loop_length)++;
					slow_iter = slow_iter->next;
				}
			}
			return true;
		}

		inline Node* SetupTag (Node *pointer)
		{
			return reinterpret_cast<Node*>(TaggedPointer::SetupTag(reinterpret_cast<intptr_t>(pointer)));
		}

		inline Node* ClearTag (Node *pointer)
		{
			return reinterpret_cast<Node*>(TaggedPointer::ClearTag(reinterpret_cast<intptr_t>(pointer)));
		}

		bool FindLoopTagged(Node *list, Node **loop_start, unsigned int *loop_length)
		{
			unsigned int list_length = 0;
			Node *iter = list;
			while (iter)
			{
				if (TaggedPointer::CheckTag(reinterpret_cast<intptr_t>(iter->next)))
				{
					// find loop
					*loop_start = ClearTag(iter);
					// clean tags
					iter = list;
					for (unsigned int i = 0; i < list_length; i++)
					{
						iter->next = ClearTag(iter->next);
						iter = iter->next;
					}
					// find length of linear part of list
					unsigned int linear_length = 0;
					iter = list;
					while (iter != *loop_start)
					{
						iter = iter->next;
						linear_length++;
					}
					*loop_length = list_length - linear_length;
					return true;
				}
				Node *next_iter = iter->next;
				iter->next = SetupTag(iter->next);
				iter = next_iter;
				list_length++;
			}
			// loop not found
			// clean tags
			iter = list;
			while (iter)
			{
				iter->next = ClearTag(iter->next);
				iter = iter->next;
			}
			return false;
		}


		Node* Clear (Node *list)
		{
			Node *loop_start = nullptr;
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

	namespace V2
	{
		Node* PushFront (Node *list, void *data)
		{
			Node *node = new Node;
			node->data = data;
			node->next = list;
			return node;
		}

		Node* Clear (Node *list)
		{
			Node *temp;
			while (list)
			{
				temp = list;
				list = list->next;
				delete temp;
			}
			return nullptr;
		}
	}
}
