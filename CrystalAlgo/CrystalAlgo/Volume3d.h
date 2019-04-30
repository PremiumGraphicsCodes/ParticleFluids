#pragma once

#include <vector>
#include "../../Crystal/Math/Box3d.h"
#include "../../Crystal/Shape/Particle.h"
#include "../../Crystal/Util/UnCopyable.h"

namespace Crystal {
	namespace Algo {

class Volume3d : private UnCopyable
{
public:
	Volume3d(const int u, const int v, const int w, const Math::Box3d& box);

	void set(const int i, const int j, const int k, double value);

	std::vector<Shape::Particle<double>> toParticles();

private:
	std::vector< std::vector< std::vector< Shape::Particle<double> > > > nodes;
};

	}
}