#include <random>
#include "dsu.h"

namespace DSU
{
void MakeDisjointSets (unsigned int *dsu_ancestors_arr, unsigned int elements_num)
{
	for (unsigned int i = 0; i < elements_num; i++)
		dsu_ancestors_arr[i] = i;
}

unsigned int Find (unsigned int *dsu_ancestors_arr, unsigned int element)
{
	return element == dsu_ancestors_arr[element] ?
	       element :
	       dsu_ancestors_arr[element] = Find(dsu_ancestors_arr, dsu_ancestors_arr[element]);
}

unsigned int Unite (unsigned int *dsu_ancestors_arr, unsigned int fst_element, unsigned int snd_element)
{
	std::bernoulli_distribution distribution;
	std::random_device generator;
	unsigned int fst_set_id = Find (dsu_ancestors_arr, fst_element),
	             snd_set_id = Find (dsu_ancestors_arr, snd_element);
	// return id of united set
	if (distribution(generator))
	{
		dsu_ancestors_arr[fst_set_id] = snd_set_id;
		return snd_set_id;
	}
	else
	{
		dsu_ancestors_arr[snd_set_id] = fst_set_id;
		return fst_set_id;
	}
}
}
