#pragma once

#include "../../Crystal/Scene/IScene.h"

//#include "MacroParticle.h"
#include "PBFluidSceneController.h"
#include "SPHKernel.h"
#include "SPHConstant.h"

namespace Crystal {
	namespace Physics {
		class PBSPHParticle;

class PBFluidScene : public Scene::IScene
{
public:
	PBFluidScene(const int id, const std::string& name, const SPHKernel& kernel, const SPHConstant& constant);

	~PBFluidScene();

	void clearParticles();

	Scene::SceneType getType() const { return Scene::SceneType::None; }

	Scene::IController* getController() { return controller.get(); }

	void addParticle(PBSPHParticle* mp) { particles.push_back(mp); }

	std::list<PBSPHParticle*> getParticles() const { return particles; }

	Math::Box3d getBoundingBox() const override;

	SPHKernel* getKernel() { return &kernel; }

	SPHConstant* getConstant() { return &constant; }

private:
	std::list<PBSPHParticle*> particles;
	std::unique_ptr<PBFluidSceneController> controller;
	SPHKernel kernel;
	SPHConstant constant;
};

	}
}
