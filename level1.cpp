#include "list.h"

int main()
{
	List::Node *list = nullptr;
	for (int i = 10; i > 0; i--)
		List::PushFront (&list, i);
	List::Print (list);
	List::Reverse (&list);
	List::Print (list);
	List::Clear (&list);
	List::Print (list);
	return 0;
}
