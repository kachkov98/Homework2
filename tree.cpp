#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"
#include "list.h"
#include "tagged_pointer.h"

namespace Tree
{
TreeNode* Node (int data, TreeNode *left, TreeNode *right)
{
	TreeNode *node = new TreeNode;
	node->data = data;
	node->left = left;
	node->right = right;
	node->parent = nullptr;
	if (left)
		node->left->parent = node;
	if (right)
		node->right->parent = node;
	return node;
}

TreeNode* GenerateTree (unsigned int nodes_number, int min_val, int max_val)
{
	assert(nodes_number && min_val <= max_val);
	int value = min_val + rand() % (max_val - min_val + 1);
	if (nodes_number == 1)
		return Node (value, nullptr, nullptr);
	if (nodes_number == 2)
		return Node(value, GenerateTree(1, min_val, max_val), nullptr);
	std::uniform_int_distribution<int> distribution (1, nodes_number - 2);
	std::random_device generator;
	unsigned int left_number = distribution(generator),
	             right_number = nodes_number - left_number - 1;
	return Node(value,
				GenerateTree( left_number, min_val, max_val),
				GenerateTree(right_number, min_val, max_val));
}

void Print (TreeNode *tree, int depth)
{
	assert(tree);
	printf ("%*s%d\n", depth, "", tree->data);
	if (tree->left)
		Print (tree->left, depth+1);
	if (tree->right)
		Print (tree->right, depth+1);
}

void PrettyPrint (TreeNode *tree)
{
	assert(tree);

	const size_t buf_max_size = 256;
	static char depth_buf[buf_max_size];
	static size_t cur_buf_size = 0;

	printf("(%d)\n", tree->data);

	if (tree->left)
	{
		for (size_t i = 0; i < cur_buf_size; i++)
			if (depth_buf[i] == ' ')
				printf ("    ");
			else if (depth_buf[i] == '|')
				printf (" |  ");
		printf (" `--");
		assert (cur_buf_size < buf_max_size);
		depth_buf[cur_buf_size++] = '|';
		PrettyPrint(tree->left);
		cur_buf_size--;
	}

	if (tree->right)
	{
		for (size_t i = 0; i < cur_buf_size; i++)
			if (depth_buf[i] == ' ')
				printf ("    ");
			else if (depth_buf[i] == '|')
				printf (" |  ");
		printf (" `--");
		assert (cur_buf_size < buf_max_size);
		depth_buf[cur_buf_size++] = ' ';
		PrettyPrint(tree->right);
		cur_buf_size--;
	}
}

int FindDistance (TreeNode *fst, TreeNode *snd)
{
	assert (fst && snd);
	int fst_depth = 0, snd_depth = 0;
	TreeNode *fst_iter = fst, *snd_iter = snd;
	while (fst_iter->parent)
	{
		fst_depth++;
		fst_iter = fst_iter->parent;
	}
	while (snd_iter->parent)
	{
		snd_depth++;
		snd_iter = snd_iter->parent;
	}
	if (fst_iter != snd_iter)
		return -1;
	int depth;
	if (fst_depth > snd_depth)
	{
		depth = fst_depth - snd_depth;
		fst_iter = fst;
		for (int i = 0; i < depth; i++)
			fst_iter = fst_iter->parent;
		snd_iter = snd;
	}
	else
	{
		depth = snd_depth - fst_depth;
		fst_iter = fst;
		snd_iter = snd;
		for (int i = 0; i < depth; i++)
			snd_iter = snd_iter->parent;
	}
	while (fst_iter->parent && snd_iter->parent && fst_iter!= snd_iter)
	{
		fst_iter = fst_iter->parent;
		snd_iter = snd_iter->parent;
		depth+=2;
	}
	return depth;
}

inline TreeNode* SetupTag (TreeNode *pointer)
{
	return reinterpret_cast<TreeNode*>(TaggedPointer::SetupTag(reinterpret_cast<intptr_t>(pointer)));
}

inline TreeNode* ClearTag (TreeNode *pointer)
{
	return reinterpret_cast<TreeNode*>(TaggedPointer::ClearTag(reinterpret_cast<intptr_t>(pointer)));
}

int FindDistanceTagged(TreeNode *fst, TreeNode *snd)
{
	assert (fst && snd);
	TreeNode *fst_iter = fst, *snd_iter = snd;
	while (fst_iter)
	{
		TreeNode *parent = fst_iter->parent;
		fst_iter->parent = SetupTag(fst_iter->parent);
		fst_iter = parent;
	}
	int ans = 0;
	while (snd_iter && !TaggedPointer::CheckTag(reinterpret_cast<intptr_t>(snd_iter->parent)))
	{
		snd_iter = snd_iter->parent;
		ans++;
	}
	if (!snd_iter)
		return  -1;
	fst_iter = fst;
	bool is_below_lca = true;
	while (fst_iter)
	{
		if (fst_iter == snd_iter)
			is_below_lca = false;
		if (is_below_lca)
			ans++;
		fst_iter = fst_iter->parent = ClearTag(fst_iter->parent);
	};
	return ans;
}


void Clear (TreeNode *tree)
{
	assert (tree);
	List::V2::Node *cur_free_list = nullptr, *next_free_list = nullptr;
	cur_free_list = List::V2::PushFront(cur_free_list, static_cast<void*> (tree));
	// while list of nodes to delete is not empty
	while (cur_free_list)
	{
		// delete nodes from cur_free_list and add nodes of left and right subtrees to next_free_list
		List::V2::Node *iter = cur_free_list;
		do
		{
			TreeNode *cur_node = static_cast<TreeNode*>(iter->data);
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
