#pragma once

#include <array>

namespace Crystal {
	namespace Search {

class ZOrderCurve2d
{
public:
	static int encode(const std::array<int,2>& index);

private:
	static int encode(int n);
};

class ZOrderCurve3d
{
public:
	static int encode(const std::array<int, 3>& index);

private:
	static int encode(int x);
};

	}
}