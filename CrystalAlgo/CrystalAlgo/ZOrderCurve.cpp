#include "ZOrderCurve.h"

using namespace Crystal::Search;

int ZOrderCurve2d::encode(const std::array<int, 2>& index)
{
	const auto ei1 = encode(index[0]);
	const auto ei2 = encode(index[1]);
	return (ei1 | (ei2 << 1));
}

int ZOrderCurve2d::encode(int n)
{
	n = (n | (n << 16)) & 0b00000000000000001111111111111111; // 0x0000ffff;
	n = (n | (n << 8))  & 0b00000000111111110000000011111111; // 0x00ff00ff;
	n = (n | (n << 4))  & 0b00001111000011110000111100001111; // 0x0f0f0f0f;
	n = (n | (n << 2))  & 0b00110011001100110011001100110011; // 0x33333333;
	n = (n | (n << 1))  & 0b01010101010101010101010101010101; // 0x55555555;
	return n;
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
	x = (x | (x << 16)) & 0x30000FF;//0b11111111000000000000000011111111; // ;
	x = (x | (x << 8))  & 0x300F00F;//0b00001111000000001111000000001111; //;
	x = (x | (x << 4))  & 0x30C30C3;//0b11000011000011000011000011000011; // ;
	x = (x | (x << 2))  & 0x9249249;//0b01001001001001001001001001001001; // ; 
	return x;
}

