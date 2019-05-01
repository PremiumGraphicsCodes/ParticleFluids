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

	int getUNum() const { return nodes.size(); }

	int getVNum() const { return nodes.front().size(); }

	int getWNum() const { return nodes.front().front().size(); }

	Math::Vector3dd getPosition(const int i, const int j, const int k) const { return nodes[i][j][k].getPosition(); }

	double getValue(const int i, const int j, const int k) const { return nodes[i][j][k].getAttribute(); }

	std::vector<Shape::Particle<double>> toParticles();

private:
	std::vector< std::vector< std::vector< Shape::Particle<double> > > > nodes;
};

	}
}