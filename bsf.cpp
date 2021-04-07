#include<algorithm>
#include<chrono>
#include<iostream>
#include<random>
#include<string>
#include<vector>
#include<finders.h>
#include<util.h>
#include"checker.hpp"
std::vector<std::string>getArgs(int argc,char**argv);
int main(int argc,char**argv)
{
	auto args = getArgs(argc, argv);
	std::vector<BiomeID>biomes;
	size_t requested = std::stoi(args[1]);
	for(size_t i=2;i<args.size();i++)
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
	size_t cnt = 0;
	for(;cnt < requested;seed = rng())
	{
		if(check_for_biomes(bmap, biomes, &lst, seed))
		{
			std::cout << seed << std::endl;
			++cnt;
		}
	}
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
