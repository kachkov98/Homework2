#include <random>
#include <stdio.h>
#include <string.h>
#include "treap.h"
#include "dsu.h"
#include "timer.h"

#define PRINTRESULTS 0

const unsigned int array_size = 1000000;
const unsigned int queries_number = 10000;

void DFS (Treap::TreapNode *cur_node, unsigned int *dsu, int *lca_class_ans,
          unsigned int *min_indices, unsigned int *max_indices, int *answers)
{
	if (cur_node->left)
	{
		DFS (cur_node->left, dsu, lca_class_ans, min_indices, max_indices, answers);
		lca_class_ans[DSU::Unite(dsu, cur_node->key, cur_node->left->key)] = cur_node->priority;
	}
	if (cur_node->right)
	{
		DFS (cur_node->right, dsu, lca_class_ans, min_indices, max_indices, answers);
		lca_class_ans[DSU::Unite(dsu, cur_node->key, cur_node->right->key)] = cur_node->priority;
	}
	for (unsigned int i = 0; i < queries_number; i++)
		if (max_indices[i] == cur_node->key)
			answers[i] = lca_class_ans[DSU::Find(dsu, min_indices[i])];
}

void TarjanRMQ (int *array, unsigned int *min_indices, unsigned int *max_indeces, int *answers)
{
	Treap::TreapNode *treap = Treap::GenerateFromArray(array, array_size);
	#if PRINTRESULTS
	Treap::PrintDotFile(treap, "treap.dot");
	#endif
	unsigned int *dsu = new unsigned int[array_size];
	DSU::MakeDisjointSets(dsu, array_size);
	int *lca_class_ans = new int[array_size];
	memcpy (lca_class_ans, array, array_size * sizeof(int));
	DFS (treap, dsu, lca_class_ans, min_indices, max_indeces, answers);
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
	unsigned int *min_indexes = new unsigned int[queries_number];
	unsigned int *max_indexes = new unsigned int[queries_number];
	for (unsigned int i = 0; i < queries_number; i++)
	{
		unsigned int fst_index = distribution(generator) - 1, snd_index = distribution(generator) - 1;
		if (fst_index < snd_index)
		{
			min_indexes[i] = fst_index;
			max_indexes[i] = snd_index;
		}
		else
		{
			min_indexes[i] = snd_index;
			max_indexes[i] = fst_index;
		}
	}
	int *answers = new int[queries_number];

	Timer::Start();
	// process queries
	TarjanRMQ(array, min_indexes, max_indexes, answers);
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
		fprintf (f, "min(%u; %u) = %d\n", min_indexes[i], max_indexes[i], answers[i]);
	fclose(f);
	#endif

	// clear arrays
	delete[] array;
	delete[] min_indexes;
	delete[] max_indexes;
	delete[] answers;
	return 0;
}
