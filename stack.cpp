#include <stdlib.h>
#include <assert.h>
#include "stack.h"

namespace TreapStack
{

const unsigned int default_stack_size = 1000;

Stack::Stack():
	tos(0),
	cur_size(default_stack_size)
{
	elements = static_cast<StackElement*>(calloc(cur_size, sizeof(StackElement)));
}

void Stack::Push(const TreapStack::StackElement& element)
{
	if (tos == cur_size)
	{
		cur_size *= 2;
		elements = static_cast<StackElement*>(realloc(static_cast<void*>(elements), cur_size));
	}
	elements[tos++] = element;
}

StackElement Stack::Pop()
{
	assert (tos);
	return elements[--tos];
}

unsigned int Stack::GetTOS()
{
	return tos;
}

Stack::~Stack()
{
	free(elements);
}
}
