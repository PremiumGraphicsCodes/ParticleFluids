#pragma once

#include <vector>
#include <list>
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Shape/IPoint.h"

#include "MicroParticle.h"
#include "MacroParticle.h"

namespace Crystal {
	namespace Algo {
		namespace Physics {

			/*
			class FluidParticleSystem : public Scene::IScene
			{

			};
			*/

			class FluidSimulator
			{
			public:
				void addParticle(MacroParticle* particle) {
					this->particles.push_back(particle);
				}

				void simulate(const double dt);

			private:
				void calculateDensity();

				void calculatePressure();

				void calculateViscosity();

			private:
				std::list<MacroParticle*> particles;
			};

		}
	}
}