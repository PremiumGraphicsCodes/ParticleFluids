#pragma once

#include "../../Crystal/Scene/IScene.h"

#include "MacroParticle.h"

namespace Crystal {
	namespace Algo {
		namespace Physics {

class FluidParticleSystem : public Scene::IScene
{
public:
	FluidParticleSystem(const int id, const std::string& name)
	{

	}

private:
	std::list<MacroParticle*> particles;
};

		}
	}
}
