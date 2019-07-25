#pragma once

#include "IScene.h"
#include "../Graphics/ICamera.h"
#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

namespace Crystal {
	namespace Scene {

class CameraScene : public IScene
{
public:
	CameraScene(const int id, const std::string& name, Graphics::ICamera* camera) :
		IScene(id, name),
		camera(camera)
	{}

	~CameraScene() {};

	Graphics::ICamera* getCamera() const { return camera; }

	SceneType getType() const override { return SceneType::LightScene; }

	void onClear() override
	{
		delete camera;
	}

	SceneViewModel toViewModel() const override { return SceneViewModel(); };

	SceneIdViewModel toIdViewModel() const override { return SceneIdViewModel(); }

private:
	Graphics::ICamera* camera;
};

	}
}