#pragma once

#include "../../../Crystal/Scene/IPresenter.h"

#include "../../../Crystal/Scene/SceneShader.h"
#include "../../../Crystal/Scene/PointShaderScene.h"

namespace Crystal {
	namespace Physics {
		class IMVPFluidScene;

class MVPFluidScenePresenter : public Scene::IPresenter
{
public:
	explicit MVPFluidScenePresenter(IMVPFluidScene* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override {};

	void updateView() override;

private:
	IMVPFluidScene* model;
	Scene::PointShaderScene* view;
};

	}
}