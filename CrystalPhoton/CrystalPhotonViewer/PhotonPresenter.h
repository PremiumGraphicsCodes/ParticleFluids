#pragma once

#include "../../Crystal/Scene/IPresenter.h"

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

	void setBlend(const bool b) { this->doBlend = b; }

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

private:
	Scene::PointShaderScene* view;
	Scene::PointShaderScene* parentIdView;
	Scene::PointShaderScene* childIdView;
	bool doBlend;
};

	}
}