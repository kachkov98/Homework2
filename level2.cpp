#include <stdio.h>
#include "tree.h"

using Tree::Node;

int main ()
{
	Tree::TreeNode *tree1 = Node(1, Node(2, Node(3), Node(4, Node(5), Node(6))), Node(7, Node(8), Node(9)));
	Tree::TreeNode *tree2 = Node(1, Node(2, Node(3, Node(4), Node(5)), Node(6)), Node(7, Node(8), Node(9)));
	printf ("Tree 1:\n");
	Tree::PrettyPrint (tree1);
	printf ("Tree 2:\n");
	Tree::PrettyPrint (tree2);
	printf ("Distance between nodes 5 and 7 in tree 1: %d\n",
			Tree::FindDistance(tree1->left->right->left, tree1->right));
	printf ("Distance between root node of tree 2: %d\n",
			Tree::FindDistance(tree2, tree2));
	printf ("Distance between node 2 of tree 1 and node 7 of tree 2: %d\n",
			Tree::FindDistance(tree1->left, tree2->right));
	Tree::Clear (tree1);
	Tree::Clear (tree2);
	return 0;
}
