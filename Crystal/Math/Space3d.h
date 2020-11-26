#pragma once

#include "Vector3d.h"
#include "ISolid3d.h"

namespace Crystal {
	namespace Math {

class Space3d
{
public:
	void add(ISolid3d* volume);

	bool isInside(const Math::Vector3dd& position) const;

private:
	std::vector<ISolid3d*> volumes;
};

	}
}

