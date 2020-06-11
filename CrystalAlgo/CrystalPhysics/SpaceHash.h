#pragma once

#include "../../Crystal/Util/UnCopyable.h"
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Shape/ParticleSystem.h"
#include <list>

namespace Crystal {
	namespace Algo {
		namespace Physics {
			class MicroParticle;
			class MacroParticle;

			class SpaceHash : private UnCopyable
			{
			public:
				SpaceHash(const double divideLength, const int tableSize);

				//void add(const Shape::IParticleSystem& particles);

				void add(MicroParticle* particle);

				std::list<MicroParticle*> getNeighbors(const Math::Vector3dd& position, MacroParticle* macro);

			private:
				std::vector<std::list<MicroParticle*>> table;

				int toHash(const Math::Vector3df& pos);

				int toHash(const std::array<int, 3>& index);

				std::array<int, 3> toIndex(const Math::Vector3df& pos);

				const double divideLength;
			};
		}
	}
}