#pragma once

#include "../../../Crystal/Scene/IPresenter.h"
#include "../../../Crystal/Scene/SceneShader.h"
#include "../../../Crystal/Scene/PointShaderScene.h"

#include "../../../Crystal/Graphics/ColorMap.h"

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

	enum class Mode
	{
		Uniform,
		Density,
	};

	void setMode(const Mode mode) { this->mode = mode; }

private:
	IMVPFluidScene* model;
	Scene::PointShaderScene* view;
	Graphics::ColorMap colorMap;
	Mode mode;
};

	}
}