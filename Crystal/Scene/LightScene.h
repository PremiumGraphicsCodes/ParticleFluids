#pragma once

#include "IScene.h"
#include "../Graphics/ColorRGBA.h"
#include "../Graphics/PointLight.h"

namespace Crystal {
	namespace Scene {

class LightScene : public IScene
{
public:
	LightScene(const int id, const std::string& name, std::unique_ptr<Graphics::PointLight> light);

	~LightScene() {};

	Graphics::PointLight* getLight() const { return light.get(); }

	SceneType getType() const override { return SceneType::LightScene; }

	IPresenter* getPresenter() override { return nullptr; }

private:
	std::unique_ptr<Graphics::PointLight> light;
};

	}
}