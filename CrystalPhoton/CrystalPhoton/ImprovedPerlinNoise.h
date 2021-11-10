#pragma once

namespace Crystal {
	namespace Photon {

class ImprovedPerlinNoise
{
public:
	ImprovedPerlinNoise();

	~ImprovedPerlinNoise();
	//void buildTable();

	double getNoise(const double x, const double y, const double z) const;
};
	}
}