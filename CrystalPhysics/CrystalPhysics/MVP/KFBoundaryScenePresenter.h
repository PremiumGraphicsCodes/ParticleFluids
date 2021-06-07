#pragma once

#include "../../Crystal/Scene/IPresenter.h"

#include "../../Crystal/Scene/SceneShader.h"
#include "../../Crystal/Scene/PointShaderScene.h"

namespace Crystal {
	namespace Physics {
		class KFBoundaryScene;

class KFBoundaryScenePresenter : public Scene::IPresenter
{
public:
	explicit KFBoundaryScenePresenter(KFBoundaryScene* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override {};

	void updateView() override;

private:
	KFBoundaryScene* model;
	Scene::PointShaderScene* view;
};

	}
}