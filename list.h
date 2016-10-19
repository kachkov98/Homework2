#pragma once

namespace List
{
	inline namespace V1
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

	namespace V2
	{
		struct Node
		{
			void *data;
			Node *next;
		};
		Node* PushFront (Node *list, void *data);
		Node* Clear (Node *list);
	}
}
