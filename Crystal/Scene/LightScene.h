#pragma once

#include "IScene.h"
#include "../Shape/ParticleSystem.h"
#include "../Graphics/ColorRGBA.h"
#include "../Graphics/PointLight.h"

namespace Crystal {
	namespace Scene {

class LightScene : public IScene
{
public:
	LightScene(const int id, const std::string& name, const Graphics::PointLight& light) :
		IScene(id,name),
		light(light)
	{}

	~LightScene() {};

	Graphics::PointLight getLight() const { return light; }

	void setLight(const Graphics::PointLight& l) { light = l; }

	/*
	void move(const Math::Vector3dd& v) override { light->move(v); }

	void transform(const Math::Matrix3dd& m) { light->transform(m); }

	void transform(const Math::Matrix4dd& m) { light->transform(m); }
	*/

	bool isNull() const { return false; }

	SceneType getType() const override { return SceneType::LightScene; }

	void onClear() override
	{

	}

	void addViewModel(SceneViewModel& viewModel) const override;

private:
	Graphics::PointLight light;
};

	}
}