#include "ZIndexedSearchAlgo.h"

using namespace Crystal::Search;

namespace {
	int ToMortonIndex(int n) {
		n = (n | (n << 8)) & 0x00ff00ff;
		n = (n | (n << 4)) & 0x0f0f0f0f;
		n = (n | (n << 2)) & 0x33333333;
		return (n | (n << 1)) & 0x55555555;
	}
}

int ZIndexedSearchAlgo::toIndex1d(unsigned int x, unsigned int y, unsigned int z)
{
	return (ToMortonIndex(x) | (ToMortonIndex(y) << 1));
}
