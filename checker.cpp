#include"checker.hpp"
bool check_for_biomes(int *bmap, const std::vector<BiomeID>&biomes,LayerStack *lst, int64_t seed)
{
	Layer *layer = lst->layers + L_VORONOI_ZOOM_1;
	std::vector<bool>conts(biomes.size(), false), want(biomes.size(), true);
	setLayerSeed(layer, seed);
	genArea(layer, bmap, START, START, SIZE, SIZE);
	for(long i=0;i<SIZE * SIZE;i++)
	{
		for(size_t j=0;j<biomes.size();j++)
		{
			if(bmap[i] == biomes[j])
				conts[j] = true;
		}
	}
	return conts == want;
}
