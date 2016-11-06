#include <random>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "treap.h"
#include "dsu.h"
#include "timer.h"
#include "stack.h"

#define PRINTRESULTS 0

const unsigned int array_size = 1000000;
const unsigned int queries_number = 10000;

struct Query
{
	unsigned int min_index, max_index;
};

int query_cmp (const void *a, const void *b)
{
	return (static_cast<const Query*>(a))->max_index - (static_cast<const Query*>(b))->max_index;
}

void DFS (Treap::TreapNode *root, unsigned int *dsu, int *lca_class_ans,
          Query *queries, int *answers)
{
	TreapStack::Stack stack;
	stack.Push(TreapStack::StackElement(root));
	while (stack.GetTOS())
		if (stack.elements[stack.GetTOS() - 1].color)
		{
			// process all queries with max_index == cur_key
			Treap::TreapNode *cur_node = stack.elements[stack.GetTOS() - 1].node;
			Query key = {0, cur_node->key};
			Query *query = static_cast<Query*>(bsearch(static_cast<const void*>(&key),
													   static_cast<const void*>(queries),
													   queries_number, sizeof(Query), query_cmp));

			if (query)
			{
				ptrdiff_t start_index = query - queries, i;
				// check others suitable queries
				for (i = start_index; i > 0 && queries[i-1].max_index == cur_node->key; i--)
					answers[i-1] = lca_class_ans[DSU::Find(dsu, queries[i-1].min_index)];
				for ( i = start_index; i < queries_number && queries[i].max_index == cur_node->key; i++)
					answers[i] = lca_class_ans[DSU::Find(dsu, queries[i].min_index)];
			}

			// unite sets
			if (cur_node->parent)
				lca_class_ans[DSU::Unite(dsu, cur_node->parent->key, cur_node->key)] = cur_node->parent->priority;

			// delete this node
			stack.Pop();
		}
		else
		{
			unsigned int index = stack.GetTOS() - 1;
			stack.elements[index].color = true;
			if (stack.elements[index].node->right)
				stack.Push(TreapStack::StackElement(stack.elements[index].node->right));
			if (stack.elements[index].node->left)
				stack.Push(TreapStack::StackElement(stack.elements[index].node->left));
		}
}

void TarjanRMQ (int *array, Query *queries, int *answers)
{
	Treap::TreapNode *treap = Treap::GenerateFromArray(array, array_size);
	#if PRINTRESULTS
	Treap::PrintDotFile(treap, "treap.dot");
	#endif
	unsigned int *dsu = new unsigned int[array_size];
	DSU::MakeDisjointSets(dsu, array_size);
	int *lca_class_ans = new int[array_size];
	memcpy (lca_class_ans, array, array_size * sizeof(int));
	qsort (static_cast<void*>(queries), queries_number, sizeof (Query), query_cmp);
	DFS (treap, dsu, lca_class_ans, queries, answers);
	delete[] dsu;
	delete[] lca_class_ans;
	Treap::Clear(treap);
}

int main ()
{
	std::uniform_int_distribution<int> distribution (1, array_size);
	std::random_device generator;

	// generate array and queries
	int *array = new int[array_size];
	for (unsigned int i = 0; i < array_size; i++)
		array[i] = distribution(generator);
	Query *queries = new Query[queries_number];
	for (unsigned int i = 0; i < queries_number; i++)
	{
		unsigned int fst_index = distribution(generator) - 1, snd_index = distribution(generator) - 1;
		if (fst_index < snd_index)
		{
			queries[i].min_index = fst_index;
			queries[i].max_index = snd_index;
		}
		else
		{
			queries[i].min_index = snd_index;
			queries[i].max_index = fst_index;
		}
	}
	int *answers = new int[queries_number];

	Timer::Start();
	// process queries
	TarjanRMQ(array, queries, answers);
	printf ("Processing time: %d ms\n", Timer::Stop());

	#if PRINTRESULTS
	FILE *f = fopen("results.txt", "w");
	if (!f)
		return EXIT_FAILURE;
	fprintf (f, "Array:\n");
	for (unsigned int i = 0; i < array_size; i++)
		fprintf (f, "%d ", array[i]);
	fprintf (f, "\nQueries and answers:\n");
	for (unsigned int i = 0; i < queries_number; i++)
		fprintf (f, "min(%u; %u) = %d\n", queries[i].min_index, queries[i].max_index, answers[i]);
	fclose(f);
	#endif

	// clear arrays
	delete[] array;
	delete[] queries;
	delete[] answers;
	return 0;
}
