#pragma once

#include "../../Crystal/Scene/IScene.h"

#include "MacroParticle.h"
#include "FluidSceneController.h"

namespace Crystal {
	namespace Algo {
		namespace Physics {
			class FluidSceneController;

class FluidScene : public Scene::IScene
{
public:
	FluidScene(const int id, const std::string& name)
	{

	}

	Scene::SceneType getType() const { return Scene::SceneType::None; }

	Scene::IController* getController() { return controller; }

private:
	std::list<MacroParticle*> particles;
	FluidSceneController* controller;
};

		}
	}
}
