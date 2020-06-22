#include "ZOrderCurve3d.h"

using namespace Crystal::Search;

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
	x = (x | (x << 16)) & 0x30000FF;//0b11111111000000000000000011111111; // ;
	x = (x | (x << 8)) & 0x300F00F;//0b00001111000000001111000000001111; //;
	x = (x | (x << 4)) & 0x30C30C3;//0b11000011000011000011000011000011; // ;
	x = (x | (x << 2)) & 0x9249249;//0b01001001001001001001001001001001; // ; 
	return x;
}

