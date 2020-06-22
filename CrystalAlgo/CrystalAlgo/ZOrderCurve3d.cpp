#include "ZOrderCurve3d.h"

using namespace Crystal::Search;

namespace {
	const auto mask16 = 0b0011111111000000000000000011111111;//0x30000FF;
	const auto mask8  = 0b0000001111000000001111000000001111;//0x300F00F;
	const auto mask4  = 0b0011000011000011000011000011000011;//0x30C30C3;
	const auto mask2  = 0b1001001001001001001001001001001001;//0x9249249;
}

int ZOrderCurve3d::encode(const std::array<int, 3>& index)
{
	const auto ei1 = encode(index[0]);
	const auto ei2 = encode(index[1]);
	const auto ei3 = encode(index[2]);

	return (ei1 | (ei2 << 1) | (ei3 << 2));
}

int ZOrderCurve3d::encode(int x)
{
	//	x = x | 0x000003ff;
	x = (x | (x << 16))& mask16;//0b11111111000000000000000011111111; // ;
	x = (x | (x << 8)) & mask8;
	x = (x | (x << 4)) & mask4;
	x = (x | (x << 2)) & mask2; 
	return x;
}

int ZOrderCurve3d::decode_(int x)
{
	x = x & mask2;
	x = (x ^ (x >> 2)) & mask4;
	x = (x ^ (x >> 4)) & mask8;
	x = (x ^ (x >> 8)) & mask16;
	x = (x ^ (x >> 16)) & mask16;
	return x;
}


