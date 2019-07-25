#pragma once

#include "IScene.h"
#include "../Graphics/ICamera.h"

namespace Crystal {
	namespace Scene {

class LightScene : public IScene
{
public:
	LightScene(const int id, const std::string& name, Graphics::ICamera* camera) :
		IScene(id, name),
		camera(camera)
	{}

	~LightScene() {};

	Graphics::ICamera* getCamera() const { return camera; }

	SceneType getType() const override { return SceneType::LightScene; }

	void onClear() override
	{
		delete camera;
	}

	SceneViewModel toViewModel() const override;

	SceneIdViewModel toIdViewModel() const override;

private:
	Graphics::ICamera* camera;
};

	}
}