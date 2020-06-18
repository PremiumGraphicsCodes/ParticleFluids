#include "ZIndexedSearchAlgo.h"

using namespace Crystal::Search;

int ZIndexedSearchAlgo::toIndex1d(unsigned int x, unsigned int y, unsigned int z)
{
	auto yy = y << 1;
	auto xx = x + yy;
	return x + yy;
}
