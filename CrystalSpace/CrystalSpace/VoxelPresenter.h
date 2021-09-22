#pragma once

#include "CrystalScene/Scene/IPresenter.h"

namespace Crystal {
	namespace Scene {
		class PointShaderScene;
	}
	namespace Space {
		class VoxelScene;

class VoxelPresenter : public Scene::IPresenter
{
public:
	explicit VoxelPresenter(VoxelScene* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

private:
	VoxelScene* model;
	Scene::PointShaderScene* view;
};

	}
}