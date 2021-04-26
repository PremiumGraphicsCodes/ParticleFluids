#pragma once

#include "../../Crystal/Scene/IPresenter.h"

#include "../../Crystal/Scene/SceneShader.h"
#include "../../Crystal/Scene/PointShaderScene.h"

namespace Crystal {
	namespace Physics {
		class IKFFluidScene;

class KFFluidScenePresenter : public Scene::IPresenter
{
public:
	explicit KFFluidScenePresenter(IKFFluidScene* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override {};

	void updateView() override;

private:
	IKFFluidScene* model;
	Scene::PointShaderScene* view;
};

	}
}