#pragma once

#include "../../Crystal/Scene/IParticleSystemPresenter.h"

namespace Crystal {
	namespace Scene {
		class PointShaderScene;
	}
	namespace Photon {
		class PhotonScene;

class PhotonPresenter : public Scene::IPresenter
{
public:
	explicit PhotonPresenter(PhotonScene* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

private:
	PhotonScene* model;
	Scene::PointShaderScene* view;
};

	}
}