#ifndef CHECKER_HPP_
#define CHECKER_HPP_
#include<vector>
#include<finders.h>
#define SIZE 3455
#define START -1727
bool check_for_biomes(int *bmap, const std::vector<BiomeID>&biomes,LayerStack *lst, int64_t seed);
#endif
