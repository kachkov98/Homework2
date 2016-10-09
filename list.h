#pragma once

namespace List
{
struct Node
{
	int data;
	Node *next;
};

void PushFront (Node **list, int data);
void Print (const Node *list);
void Reverse (Node **list);
void Clear (Node **list);
}
