#pragma once

#include "../../Crystal/Scene/IParticleSystemScene.h"

#include "KFMacroParticle.h"
#include "KFFluidScenePresenter.h"
#include "KFFluidEmitter.h"

namespace Crystal {
	namespace Physics {
		class KFFluidScenePresenter;

class KFFluidScene : public Scene::IParticleSystemScene
{
public:
	KFFluidScene(const int id, const std::string& name);

	~KFFluidScene();

	static constexpr auto Type = "KFFluid";

	Scene::SceneType getType() const { return Type; }

	Scene::IPresenter* getPresenter() { return controller.get(); }

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

	bool isBoundary() const { return isBoundary_; }

	void setBoundary(const bool isBoundary_) { this->isBoundary_ = isBoundary_; }

	void translate(const Math::Vector3dd& v) override { ; }

	void transform(const Math::Matrix3dd& m) override { ; }

	void transform(const Math::Matrix4dd& m) override { ; }

	std::vector<Math::Vector3dd> getPositions() const override;

	void addEmitter(const KFFluidEmitter& emitter) { this->emitters.push_back(emitter); }

	void emitParticles(const int timeStep);

private:
	std::vector<KFMacroParticle*> particles;
	float pressureCoe;
	float viscosityCoe;
	std::unique_ptr<KFFluidScenePresenter> controller;
	std::vector<KFFluidEmitter> emitters;
	bool isBoundary_;
};


	}
}
