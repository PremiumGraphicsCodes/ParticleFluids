#pragma once

#include "Volume3d.h"
#include <functional>

namespace Crystal {
	namespace Algo {

class VolumeBuilder
{
public:
	VolumeBuilder(const int unum, const int vnum, const int wnum, const Math::Box3d& box);

	void build( const std::function<double(double)>& function);

	Volume3d&& getVolume() { return std::move(volume); }

private:
	Volume3d volume;
};

	}
}