#pragma once

#include <array>

namespace Crystal {
	namespace Search {

class ZOrderCurve2d
{
public:
	int encode(const std::array<int,2>& index);

	std::array<int,2> decode(int x);

private:
	int encode(int n);

	int decode_(int x);
};

	}
}