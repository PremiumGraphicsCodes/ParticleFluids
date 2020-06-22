#pragma once

#include <array>

namespace Crystal {
	namespace Search {

class ZOrderCurve3d
{
public:
	int encode(const std::array<int, 3>& index);

private:
	int encode(int x);

	int decode_(int x);
};

	}
}