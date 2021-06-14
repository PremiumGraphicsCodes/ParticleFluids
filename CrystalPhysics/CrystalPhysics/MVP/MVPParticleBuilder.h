#pragma once

#include <vector>
#include "../../../Crystal/Shape/Volume.h"

namespace Crystal {
	namespace Physics {

class MVPParticleBuilder
{
public:
	void buildTable(const int unum, const int vnum, const int wnum);

	//void create(const Math::Vector3dd& center);

	//float calculateWeight(const float a, const float r);

	float calculateWeight(const float r, const float dr);


private:
	struct Cell
	{
		Math::Vector3df position;
		Math::Vector3df length;
		double value;
	};

	std::vector<std::vector<std::vector<Cell>>> cells;
};
	}
}