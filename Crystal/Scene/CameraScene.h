#pragma once

#include "IScene.h"
#include "../Graphics/ColorRGBA.h"
#include "../Graphics/ICamera.h"

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

	Graphics::ICamera* getCamera() const { return camera.get(); }

	/*
	void move(const Math::Vector3dd& v) override { light->move(v); }

	void transform(const Math::Matrix3dd& m) { light->transform(m); }

	void transform(const Math::Matrix4dd& m) { light->transform(m); }
	*/

	SceneType getType() const override { return SceneType::CameraScene; }

	void onClear() override
	{

	}

	void toViewModel(SceneViewModel& viewModel) const override {}

	void toIdViewModel(SceneIdViewModel& viewModel) const override {}

private:
	std::unique_ptr< Graphics::ICamera > camera;
};

	}
}