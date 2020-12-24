#pragma once

#include "../../Crystal/Scene/IPresenter.h"

#include "../../Crystal/Scene/SceneShader.h"
#include "../../Crystal/Scene/LineShaderScene.h"

namespace Crystal {
	namespace Physics {
		class CSGBoundaryScene;

class CSGBoundaryScenePresenter : public Scene::IPresenter
{
public:
	explicit CSGBoundaryScenePresenter(CSGBoundaryScene* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override {};

	void updateView() override;

private:
	CSGBoundaryScene* model;
	Scene::LineShaderScene* view;
};

	}
}