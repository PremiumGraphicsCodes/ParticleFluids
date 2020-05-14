#pragma once

#include "IScene.h"
#include "../Graphics/ColorRGBA.h"
#include "../Graphics/PointLight.h"
#include "LightController.h"

namespace Crystal {
	namespace Scene {

class LightScene : public IScene
{
public:
	LightScene(const int id, const std::string& name, std::unique_ptr<Graphics::PointLight> light);

	~LightScene() {};

	Graphics::PointLight* getLight() const { return light.get(); }

	/*
	void move(const Math::Vector3dd& v) override { light->move(v); }

	void transform(const Math::Matrix3dd& m) { light->transform(m); }

	void transform(const Math::Matrix4dd& m) { light->transform(m); }
	*/

	SceneType getType() const override { return SceneType::LightScene; }

	IController* getController() override { return &controller; }

private:
	std::unique_ptr<Graphics::PointLight> light;
	LightController controller;
};

	}
}