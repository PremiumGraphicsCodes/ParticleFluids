#pragma once

#include "../../../Crystal/Scene/IPresenter.h"

#include "../../../Crystal/Scene/SceneShader.h"
#include "../../../Crystal/Scene/PointShaderScene.h"

namespace Crystal {
	namespace Physics {
		class MVPBoundaryScene;

class KFBoundaryScenePresenter : public Scene::IPresenter
{
public:
	explicit KFBoundaryScenePresenter(MVPBoundaryScene* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override {};

	void updateView() override;

private:
	MVPBoundaryScene* model;
	Scene::PointShaderScene* view;
};

	}
}