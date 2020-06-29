#pragma once

#include "../../Crystal/Util/UnCopyable.h"
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Shape/ParticleSystem.h"
#include <list>
#include <functional>

namespace Crystal {
	namespace Physics {
		class MicroParticle;
		class MacroParticle;

class SpaceHash : private UnCopyable
{
public:
	SpaceHash(const double divideLength, const int tableSize);

	//void add(const Shape::IParticleSystem& particles);

	void add(MacroParticle* particle);

	void solveInteractions(MicroParticle* micro, const std::function<void(MacroParticle*, Shape::IPoint*)>& func);

private:
	std::vector<std::list<MacroParticle*>> table;

	int toHash(const Math::Vector3df& pos);

	int toHash(const std::array<int, 3>& index);

	std::array<int, 3> toIndex(const Math::Vector3df& pos);

	const double divideLength;
};

	}
}