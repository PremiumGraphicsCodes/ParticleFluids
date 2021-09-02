#include "Octree.h"

#include "../../Crystal/Shape/IParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

Octree::Octree(const Box3dd& space) :
	space(space)
{}

void Octree::add(IParticle* particle)
{
	//const auto& position = particle->getPosition();
	this->particles.push_back(particle);
}

void Octree::createChildren() const
{
	/*
	const auto& spaces = this->space.getSubSpaces(2, 2, 2);
	assert(spaces.size() == 8);
	*/

	std::vector<Octree> results;
	/*
	for (int i = 0; i < 8; ++i) {
		Octree result(spaces[i]);
		for (const auto p : particles) {
			if (result.isNeighbor(p)) {
				result.add(p);
			}
		}
		if (!result.isEmpty()) {
			results.push_back(result);
		}
	}
	*/
}

bool Octree::isEmpty() const
{
	return particles.empty();
}
