#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"
#include "timer.h"

using Tree::Node;

const unsigned int nodes_number = 1000;

Tree::TreeNode* RandomNode (Tree::TreeNode *tree)
{
	if (tree->left && tree->right)
		return RandomNode (rand() % 2 ? tree->right : tree->left);
	else if (tree->left && !tree->right)
		return RandomNode(tree->left);
	else if (tree->right && !tree->left)
		return RandomNode(tree->right);
	else
		return tree;
}

int main ()
{
	srand(time(nullptr));

	Tree::TreeNode *tree = Tree::GenerateTree(nodes_number, 1, 9);
	Tree::TreeNode *node1 = RandomNode(tree), *node2 = RandomNode(tree);
	#if 0
	printf ("Tree:\n");
	Tree::PrettyPrint (tree);
	printf ("Distance between nodes %d and %d: %d\n",
	        node1->data, node2->data, FindDistance(node1, node2));
	printf ("DistanceTagged between nodes %d and %d: %d\n",
	        node1->data, node2->data, FindDistanceTagged(node1, node2));
	#endif
	#if 1
	int distance;

	Timer::Start();
	for (int i = 0; i < 1000000; i++)
		distance = Tree::FindDistance(node1, node2);
	printf ("Distance: %d time: %u\n", distance, Timer::Stop());

	Timer::Start();
	for (int i = 0; i < 1000000; i++)
		distance = Tree::FindDistanceTagged(node1, node2);
	printf ("TaggedDistance: %d time: %u\n", distance, Timer::Stop());
	#endif
	Tree::Clear (tree);
	return 0;
}
