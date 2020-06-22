#pragma once

#include <array>

namespace Crystal {
	namespace Search {

class ZOrderCurve3d
{
public:
	static int encode(const std::array<int, 3>& index);

private:
	static int encode(int x);
};

	}
}