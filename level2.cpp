#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"

using Tree::Node;

int main ()
{
	srand(time(nullptr));

	Tree::TreeNode *tree1 = Tree::GenerateTree(20, 1, 9);
	Tree::TreeNode *tree2 = Tree::GenerateTree(20, 1, 9);
	printf ("Tree 1:\n");
	Tree::PrettyPrint (tree1);
	printf ("Tree 2:\n");
	Tree::PrettyPrint (tree2);
	printf ("Distance between nodes in tree 1: %d\n",
			Tree::FindDistance(tree1->left, tree1->right));
	printf ("Distance between root node of tree 2: %d\n",
			Tree::FindDistance(tree2, tree2));
	printf ("Distance between node 2 of tree 1 and node 7 of tree 2: %d\n",
			Tree::FindDistance(tree1->left, tree2->right));
	Tree::Clear (tree1);
	Tree::Clear (tree2);
	return 0;
}
