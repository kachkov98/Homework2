#include <stdio.h>
#include <assert.h>
#include "tree.h"

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
		assert (cur_buf_size < buff_max_size);
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
		assert (cur_buf_size < buff_max_size);
		depth_buf[cur_buf_size++] = ' ';
		PrettyPrint(tree->right);
		cur_buf_size--;
	}
}

int FindDistance (TreeNode *fst, TreeNode *snd)
{
	assert (fst && snd);
	const size_t max_stack_size = 256;
	TreeNode* fst_stack[max_stack_size];
	TreeNode* snd_stack[max_stack_size];
	size_t fst_tos = 0, snd_tos = 0; // top of stack

	while (fst)
	{
		fst_stack[fst_tos++] = fst;
		fst = fst->parent;
	}

	while (snd)
	{
		snd_stack[snd_tos++] = snd;
		snd = snd->parent;
	}

	// nodes haven't got common ancestor
	if (fst_stack[fst_tos-1] != snd_stack[snd_tos-1])
		return -1;

	// delete the same nodes from both stacks
	while (fst_tos > 0 && snd_tos > 0 && fst_stack[fst_tos-1]==snd_stack[snd_tos-1])
	{
		--fst_tos;
		--snd_tos;
	}
	return fst_tos + snd_tos;
}

void Clear (TreeNode *tree)
{
	assert (tree);
	if (tree->left)
		Clear (tree->left);
	if (tree->right)
		Clear(tree->right);
	delete tree;
}
}
