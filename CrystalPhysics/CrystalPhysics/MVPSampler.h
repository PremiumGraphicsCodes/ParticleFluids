#pragma once

#include <list>

namespace Crystal {
	namespace Physics {
		class MVPFluidScene;

class MVPSampler
{
public:
	void merge(const std::list<MVPFluidScene*>& fluids, const double searchRadius);

	void split(const std::list<MVPFluidScene*>& fluids);
};
	}
}