#pragma once

#include "../../Crystal/Scene/IParticleSystemScene.h"
//#include "ParticleAttribute.h"

//#include "IParticleSystemScene.h"
#include "../../Crystal/Scene/ParticleSystemPresenter.h"

namespace Crystal {
	namespace Photon {
		class Photon;

class PhotonScene : public Scene::IParticleSystemScene
{
public:
	//PhotonScene();

	PhotonScene(const int id, const std::string& name);

	~PhotonScene() {};

	void translate(const Math::Vector3dd& v) override { ; }

	void transform(const Math::Matrix3dd& m) override { ; }

	void transform(const Math::Matrix4dd& m) override { ; }

	static Scene::SceneType getTypeName() { return Scene::SceneType("photon"); }

	Scene::SceneType getType() const override { return getTypeName(); }

	Math::Box3d getBoundingBox() const override;

	std::vector<Math::Vector3dd> getPositions() const override;

	Scene::IParticleSystemPresenter* getPresenter() { return presenter.get(); }

private:
	std::vector<Photon*> photons;
	//std::unique_ptr< Shape::ParticleSystem<ParticleAttribute> > shape;
	std::unique_ptr< Scene::IParticleSystemPresenter > presenter;
};

	}
}