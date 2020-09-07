#pragma once

#include "../../Crystal/Scene/IPresenter.h"

#include "../../Crystal/Scene/SceneShader.h"
#include "../../Crystal/Scene/PointShaderScene.h"

namespace Crystal {
	namespace Physics {
		class KFFluidScene;

class KFFluidScenePresenter : public Scene::IPresenter
{
public:
	explicit KFFluidScenePresenter(KFFluidScene* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

private:
	KFFluidScene* model;
	Scene::PointShaderScene* view;
};

	}
}