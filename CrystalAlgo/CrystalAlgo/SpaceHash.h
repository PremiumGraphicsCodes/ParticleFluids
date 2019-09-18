#pragma once

#include "../../Crystal/Util/UnCopyable.h"
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Scene/ParticleSystem.h"
#include <list>

namespace Crystal {
	namespace Algo {

class SpaceHash : private UnCopyable
{
public:
	SpaceHash(const float divideLength, const int tableSize);

	//void add(const Shape::IParticleSystem& particles);

	void add(Shape::IParticle* particle);

	std::list<Shape::IParticle*> getNeighbors(const Math::Vector3dd& position);

private:
	std::vector<std::list<Shape::IParticle*>> table;

	int toHash(const Math::Vector3df& pos);

	int toHash(const std::array<int, 3>& index);

	std::array<int, 3> toIndex(const Math::Vector3df& pos);

	const float divideLength;


};
	}
}