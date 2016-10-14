#include <stdio.h>
#include "list.h"

int main()
{
	// create list
	List::Node *list = nullptr;
	List::Node *node2, *node5;
			list = List::PushFront(list, 1);
	node2 = list = List::PushFront(list, 2);
			list = List::PushFront(list, 3);
			list = List::PushFront(list, 4);
	node5 = list = List::PushFront(list, 5);
	// test Print()
	List::Print(list);
	// test Reverse()
	list = List::Reverse(list);
	List::Print(list);
	// make loop
	node5->next = node2;
	// test FindLoop()
	List::Node *loop_start;
	unsigned int loop_length;
	if (List::FindLoop(list, &loop_start, &loop_length))
		printf ("Loop starts from element: %d; loop length: %u\n", loop_start->data, loop_length);
	// test Print() for loops
	List::Print (list);
	// test Clear()
	list = List::Clear (list);
	List::Print (list);
	return 0;
}
