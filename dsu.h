#pragma once

namespace DSU
{
void MakeDisjointSets (unsigned int *dsu_ancestors_arr, unsigned int elements_num);
unsigned int Find (unsigned int *dsu_ancestors_arr, unsigned int element);
unsigned int Unite (unsigned int *dsu_ancestors_arr, unsigned int fst_element, unsigned int snd_element);
}
