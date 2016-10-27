#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "timer.h"

const unsigned int nodes_number = 10000;

int main()
{
	srand(time(nullptr));
	// create list
	List::Node *list = List::GenerateList(nodes_number, 1, 9);
	List::Node *list_end = list;
	list = List::Reverse(list);
	unsigned int loop_pos = rand () % nodes_number;
	List::Node *loop_pos_ptr = list;
	for (unsigned int i = 0; i < loop_pos; i++)
		loop_pos_ptr = loop_pos_ptr->next;
	list_end->next = loop_pos_ptr;

	// for checking FindLoop() and FindLoopTagged()
	#if 0
	List::Print (list);
	List::Node *loop_start;
	unsigned int loop_length;
	List::FindLoop(list, &loop_start, &loop_length);
	printf ("Loop length: %u\n", loop_length);
	List::FindLoopTagged(list, &loop_start, &loop_length);
	printf ("LoopTagged length: %u\n", loop_length);
	#endif
	// benchmark FindLoop()
	List::Node *loop_start;
	unsigned int loop_length;

	Timer::Start();
	for (unsigned int i = 0; i < 1000; i++)
		List::FindLoop(list, &loop_start, &loop_length);
	printf (" First method loop length: %u time: %d ms\n", loop_length, Timer::Stop());

	Timer::Start();
	for (unsigned int i = 0; i < 1000; i++)
		List::FindLoopTagged(list, &loop_start, &loop_length);
	printf ("Second method loop length: %u time: %d ms\n", loop_length, Timer::Stop());

	// clear list
	list = List::Clear (list);
	return 0;
}
