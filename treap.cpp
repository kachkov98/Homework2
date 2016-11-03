#include <stdio.h>
#include <assert.h>
#include "treap.h"
#include "list.h"

namespace Treap
{
TreapNode* Node (unsigned int key, int priority, TreapNode *parent, TreapNode *left, TreapNode *right)
{
	TreapNode *node = new TreapNode;
	node->key = key;
	node->priority = priority;
	node->parent = parent;
	node->left = left;
	node->right = right;
	if (left)
		node->left->parent = node;
	if (right)
		node->right->parent = node;
	return node;
}

TreapNode* GenerateFromArray (int *array, unsigned int array_size)
{
	assert (array && array_size);
	TreapNode *last_node = Node(0, array[0]);
	for (unsigned int i = 1; i < array_size; i++)
	{
		if (array[i] > last_node->priority)
			last_node = last_node->right = Node(i, array[i], last_node);
		else
		{
			TreapNode *cur_node = last_node;
			while (cur_node->parent && cur_node->priority >= array[i])
				cur_node = cur_node->parent;
			if (cur_node->priority >= array[i])
				last_node = Node(i, array[i], nullptr, cur_node);
			else
				cur_node->right = last_node = Node (i, array[i], cur_node, cur_node->right);
		}
	}
	while (last_node->parent)
		last_node = last_node->parent;
	return last_node;
}

void PrettyPrint (TreapNode *treap)
{
	assert(treap);

	const size_t buf_max_size = 256;
	static char depth_buf[buf_max_size];
	static size_t cur_buf_size = 0;

	printf("(%u %d)\n", treap->key, treap->priority);

	if (treap->left)
	{
		for (size_t i = 0; i < cur_buf_size; i++)
			if (depth_buf[i] == ' ')
				printf ("    ");
			else if (depth_buf[i] == '|')
				printf (" |  ");
		printf (" `--");
		assert (cur_buf_size < buf_max_size);
		depth_buf[cur_buf_size++] = '|';
		PrettyPrint(treap->left);
		cur_buf_size--;
	}

	if (treap->right)
	{
		for (size_t i = 0; i < cur_buf_size; i++)
			if (depth_buf[i] == ' ')
				printf ("    ");
			else if (depth_buf[i] == '|')
				printf (" |  ");
		printf (" `--");
		assert (cur_buf_size < buf_max_size);
		depth_buf[cur_buf_size++] = ' ';
		PrettyPrint(treap->right);
		cur_buf_size--;
	}
}

void PrintDotNodes (TreapNode *treap, FILE *f)
{
	fprintf (f, "%u [label=\"%u; %d\"]\n", treap->key, treap->key, treap->priority);
	if (treap->left)
	{
		fprintf (f, "%u -> %u [color=red]\n", treap->key, treap->left->key);
		PrintDotNodes(treap->left, f);
	}
	if (treap->right)
	{
		fprintf (f, "%u -> %u [color=blue]\n", treap->key, treap->right->key);
		PrintDotNodes(treap->right, f);
	}
}

void PrintDotFile (TreapNode *treap, const char *file_name)
{
	assert(treap);
	FILE *f = fopen(file_name, "w");
	if (!f)
		return;
	fprintf (f, "digraph treap\n{\n");
	PrintDotNodes(treap, f);
	fprintf (f, "}\n");
	fclose(f);
}

void Clear (TreapNode *treap)
{
	assert (tree);
	List::V2::Node *cur_free_list = nullptr, *next_free_list = nullptr;
	cur_free_list = List::V2::PushFront(cur_free_list, static_cast<void*> (treap));
	// while list of nodes to delete is not empty
	while (cur_free_list)
	{
		// delete nodes from cur_free_list and add nodes of left and right subtrees to next_free_list
		List::V2::Node *iter = cur_free_list;
		do
		{
			TreapNode *cur_node = static_cast<TreapNode*>(iter->data);
			if (cur_node->left)
				next_free_list = List::V2::PushFront(next_free_list, cur_node->left);
			if (cur_node->right)
				next_free_list = List::V2::PushFront(next_free_list, cur_node->right);
			delete cur_node;
			iter = iter->next;
		}
		while (iter);
		cur_free_list = List::V2::Clear(cur_free_list);
		// swap pointers to lists
		List::V2::Node *tmp = cur_free_list;
		cur_free_list = next_free_list;
		next_free_list = tmp;
	}
}
}
