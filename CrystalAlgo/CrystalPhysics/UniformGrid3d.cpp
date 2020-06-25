#include "UniformGrid3d.h"

#include "../../Crystal/Shape/IPoint.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Physics;

UniformGrid3d::UniformGrid3d(const double divideLength, const Vector3dd& min) :
	divideLength(divideLength)
{
}

/*
void SpaceHash::add(const IParticleSystem& particles)
{
	const auto& points = particles.getIParticles();
	for (auto p : points) {
		add(p);
	}
}
*/

void UniformGrid3d::add(IPoint* particle)
{
	const auto& index = toIndex(particle->getPosition());
	grid[index[0]][index[1]][index[2]].push_back( particle );
}
