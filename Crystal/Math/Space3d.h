#pragma once

#include "Vector3d.h"
#include "IVolume3d.h"

namespace Crystal {
	namespace Math {

class Space3d
{
public:
	void add(IVolume3d* volume);

	bool isInside(const Math::Vector3dd& position) const;

private:
	std::vector<IVolume3d*> volumes;
};

	}
}

