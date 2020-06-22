#pragma once

#include <array>

namespace Crystal {
	namespace Search {

class ZOrderCurve2d
{
public:
	unsigned int encode(const std::array<unsigned int,2>& index) const;

	std::array<unsigned int,2> decode(unsigned int x) const;

private:
	unsigned int encode(unsigned int n) const;

	unsigned int decode_(unsigned int x) const;
};

	}
}