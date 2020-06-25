#pragma once

#include "../../Crystal/Scene/IScene.h"

#include "MacroParticle.h"
#include "FluidSceneController.h"

namespace Crystal {
	namespace Physics {
		class FluidSceneController;

class FluidScene : public Scene::IScene
{
public:
	FluidScene(const int id, const std::string& name);

	~FluidScene();

	Scene::SceneType getType() const { return Scene::SceneType::None; }

	Scene::IController* getController() { return controller.get(); }

	void addParticle(MacroParticle* mp) { particles.push_back(mp); }

	std::list<MacroParticle*> getParticles() const { return particles; }

	void clearParticles();

	Math::Box3d getBoundingBox() const override;

private:
	std::list<MacroParticle*> particles;
	std::unique_ptr<FluidSceneController> controller;
};

	}
}
