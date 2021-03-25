#pragma once

#include "../../Crystal/Scene/IPresenter.h"

namespace Crystal {
	namespace Scene{
		class PointShaderScene;
	}
	namespace Space {
		class SparseVolumeScene;

class SparseVolumePresenter : public Scene::IPresenter
{
public:
	explicit SparseVolumePresenter(SparseVolumeScene* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

private:
	Scene::PointShaderScene* view;
	SparseVolumeScene* model;
	//PointShaderScene* parentIdView;
	//PointShaderScene* childIdView;
};

	}
}