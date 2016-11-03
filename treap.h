#pragma once

namespace Treap
{
struct TreapNode
{
	unsigned int key;
	int priority;
	TreapNode *left, *right, *parent;
};

TreapNode* Node (unsigned int key, int priority, TreapNode *parent = nullptr,
                 TreapNode *left = nullptr, TreapNode *right = nullptr);
TreapNode* GenerateFromArray (int *array, unsigned int array_size);
void PrettyPrint (TreapNode *treap);
void PrintDotFile (TreapNode *treap, const char *file_name);
void Clear (TreapNode *treap);
}
