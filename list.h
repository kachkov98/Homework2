#pragma once

namespace List
{
struct Node
{
	int data;
	Node *next;
};

Node* PushFront (Node *list, int data);
void Print (Node *list);
Node* Reverse (Node *list);
bool FindLoop (Node *list, Node **loop_start, unsigned int *loop_length);
Node* Clear (Node *list);
}
