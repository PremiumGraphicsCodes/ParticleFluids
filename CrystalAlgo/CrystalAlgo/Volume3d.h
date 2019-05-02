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
	Volume3d(const int unum, const int vnum, const int wnum, const Math::Box3d& box);

	void set(const int u, const int v, const int w, const double value);

	int getUNum() const { return unum; }

	int getVNum() const { return vnum; }

	int getWNum() const { return wnum; }

	Math::Vector3dd getPosition(const int i, const int j, const int k) const { return nodes[i][j][k].getPosition(); }

	double getValue(const int i, const int j, const int k) const { return nodes[i][j][k].getAttribute(); }

	std::vector<Shape::Particle<double>> toParticles() const;

private:
	std::vector< std::vector< std::vector< Shape::Particle<double> > > > nodes;
	const int unum;
	const int vnum;
	const int wnum;
};

	}
}