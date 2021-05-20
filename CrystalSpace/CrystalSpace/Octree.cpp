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

std::vector< Octree > Octree::createChildren() const
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
	return std::move(results);
}

std::vector<Octree> Octree::createChildren(const int depth) const
{
	assert(depth >= 0);

	if (depth == 0) {
		return{ *this };
	}
	if (depth == 1) {
		return std::move(createChildren());
	}
	const auto& children = createChildren();
	std::vector<Octree> results;
	for (const auto& child : children) {
		const auto& rs = child.createChildren(depth - 1);
		results.insert(results.end(), rs.begin(), rs.end());
	}
	return std::move(results);
}


bool Octree::isEmpty() const
{
	return particles.empty();
}

bool Octree::equals(const Octree& rhs, const double tolerance) const
{
	return
		(this->space.isSame(rhs.space, tolerance)) &&
		(this->particles == rhs.particles);
}
