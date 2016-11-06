#pragma once
#include "treap.h"

namespace TreapStack
{
struct StackElement
{
	Treap::TreapNode *node;
	bool color;
	StackElement (Treap::TreapNode *node_ = nullptr, bool color_ = false):
		node(node_),
		color(color_)
	{}
};

class Stack
{
public:
	Stack ();
	void Push (const StackElement& element);
	StackElement Pop ();
	unsigned int GetTOS ();
	~Stack ();

	StackElement *elements;

private:
	unsigned int tos, cur_size;
};
}
