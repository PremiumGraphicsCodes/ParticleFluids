#pragma once

#include "../../Crystal/Scene/IParticleSystemScene.h"

#include "KFMacroParticle.h"
#include "KFFluidScenePresenter.h"

namespace Crystal {
	namespace Physics {
//		class KFFluidScenePresenter;

class IKFFluidScene : public Scene::IParticleSystemScene
{
public:
	IKFFluidScene(const int id, const std::string& name);

	virtual ~IKFFluidScene();

	void addParticle(KFMacroParticle* mp) {
		mp->setPressureCoe(this->pressureCoe);
		mp->setViscosityCoe(this->viscosityCoe);
		particles.push_back(mp);
	}

	std::vector<KFMacroParticle*> getParticles() const { return particles; }

	void clearParticles();

	Math::Box3d getBoundingBox() const override;

	void setPressureCoe(const float coe) { this->pressureCoe = coe; }

	float getPressure() const { return this->pressureCoe; }

	void setViscosityCoe(const float coe) { this->viscosityCoe = coe; }

	float getViscosityCoe() const { return this->viscosityCoe; }

	void translate(const Math::Vector3dd& v) override { ; }

	void transform(const Math::Matrix3dd& m) override { ; }

	void transform(const Math::Matrix4dd& m) override { ; }

	std::vector<Math::Vector3dd> getPositions() const override;

	Scene::IPresenter* getPresenter() { return controller.get(); }

private:
	std::unique_ptr<KFFluidScenePresenter> controller;
	std::vector<KFMacroParticle*> particles;
	float pressureCoe;
	float viscosityCoe;
};

	}
}