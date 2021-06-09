#pragma once

#include "../../../Crystal/Scene/IPresenter.h"

#include "../../../Crystal/Scene/SceneShader.h"
#include "../../../Crystal/Scene/PointShaderScene.h"

#include "../../../Crystal/Graphics/ColorMap.h"

namespace Crystal {
	namespace Physics {
		class SPHFlameScene;

class SPHFlameScenePresenter : public Scene::IPresenter
{
public:
	explicit SPHFlameScenePresenter(SPHFlameScene* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override{};

	void updateView() override;

	enum class Mode
	{
		Uniform,
		Temperature,
		Fuel,
	};

	void setMode(const Mode mode) { this->mode = mode; }

private:
	SPHFlameScene* model;
	Scene::PointShaderScene* view;
	Graphics::ColorMap colorMap;
	Mode mode;
};

	}
}