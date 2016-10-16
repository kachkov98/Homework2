#pragma once

namespace Tree
{
struct TreeNode
{
	int data;
	TreeNode *left, *right, *parent;
};

TreeNode* Node (int data, TreeNode *left = nullptr, TreeNode *right = nullptr);
void Print (TreeNode *tree, int depth = 0);
void PrettyPrint (TreeNode *tree);
int FindDistance (TreeNode *fst, TreeNode *snd);
void Clear (TreeNode *tree);
}
