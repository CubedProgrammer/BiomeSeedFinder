#include<algorithm>
#include<chrono>
#include<iostream>
#include<random>
#include<string>
#include<vector>
#include<finders.h>
#include<util.h>
#define SIZE 3455
#define START -1727
std::vector<std::string>getArgs(int argc,char**argv);
int main(int argc,char**argv)
{
	auto args = getArgs(argc, argv);
	std::vector<BiomeID>biomes;
	for(size_t i=1;i<args.size();i++)
		biomes.push_back(static_cast<BiomeID>(std::stoi(args[i])));
	using std::chrono::system_clock;
	auto currt = system_clock::now().time_since_epoch();
	std::mt19937_64 rng(currt.count());
	initBiomes();
	LayerStack lst;
	setupGenerator(&lst, MC_1_16);
	Layer *layer = lst.layers + L_VORONOI_ZOOM_1;
	int *bmap = allocCache(layer, SIZE, SIZE);
#ifdef _WIN32
	long long seed = rng();
#else
	long seed = rng();
#endif
	bool cont = false;
	std::vector<char>conts(biomes.size());
	std::vector<int>posi(biomes.size());
	const std::vector<char>wanted(biomes.size(), 1);
	for(;!cont;seed = rng())
	{
		setLayerSeed(layer, seed);
		layer = lst.layers + L_VORONOI_ZOOM_1;
		genArea(layer, bmap, START, START, SIZE, SIZE);
		std::fill(conts.begin(), conts.end(), false);
		std::fill(posi.begin(), posi.end(), 0);
		for(long i=0;i<SIZE * SIZE;i++)
		{
			for(size_t j=0;j<biomes.size();j++)
			{
				if(bmap[i] == biomes[j])
				{
					conts[j] = 1;
					posi[j] = i;
				}
			}
		}
		if(conts == wanted)
		{
			cont = true;
			std::cout << seed << std::endl;
		}
	}
	for(unsigned long i=0;i<posi.size();i++)
		std::cout << START + posi[i] % SIZE << ' ' << START + posi[i] / SIZE << std::endl;
	free(bmap);
	return 0;
}
std::vector<std::string>getArgs(int argc,char**argv)
{
	std::vector<std::string>vec(argc);
	for(auto &x : vec)
		x = *argv++;
	return vec;
}
