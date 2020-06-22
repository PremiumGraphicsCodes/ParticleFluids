#pragma once

#include <array>

namespace Crystal {
	namespace Search {

class ZOrderCurve3d
{
public:
	unsigned int encode(const std::array<unsigned int, 3>& index) const;

	std::array<unsigned int,3> decode(const unsigned int x) const;

private:
	unsigned int encode(unsigned int x) const;

	unsigned int decode_(unsigned int x) const;
};

	}
}