#pragma once

#include "CrystalScene/Scene/IParticleSystemScene.h"

#include "MVPVolumeParticle.h"
#include "MVPFluidScenePresenter.h"

namespace Crystal {
	namespace Physics {
//		class KFFluidScenePresenter;

class IMVPFluidScene : public Scene::IParticleSystemScene
{
public:
	IMVPFluidScene(const int id, const std::string& name);

	virtual ~IMVPFluidScene();

	void addParticle(MVPVolumeParticle* mp) {
		mp->setPressureCoe(this->pressureCoe);
		mp->setViscosityCoe(this->viscosityCoe);
		particles.push_back(mp);
	}

	std::list<MVPVolumeParticle*> getParticles() const { return particles; }

	void remove(MVPVolumeParticle* p) { particles.remove(p); }

	void add(MVPVolumeParticle* p) { particles.push_back(p); }

	void clearParticles();

	Math::Box3dd getBoundingBox() const override;

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
	std::unique_ptr<MVPFluidScenePresenter> controller;
	std::list<MVPVolumeParticle*> particles;
	float pressureCoe;
	float viscosityCoe;
};

	}
}