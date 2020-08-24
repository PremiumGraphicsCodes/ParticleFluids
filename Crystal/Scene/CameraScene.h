#pragma once

#include "IScene.h"
#include "../Graphics/Camera.h"

#include "CameraPresenter.h"

namespace Crystal {
	namespace Scene {

class CameraScene : public IScene
{
public:
	CameraScene(const int id, const std::string& name, Graphics::Camera* camera);

	~CameraScene() {};

	Graphics::Camera* getCamera() const { return camera.get(); }

	CameraPresenter* getController() { return controller.get(); }

	SceneType getType() const { return SceneType::CameraScene; }

private:
	std::unique_ptr< Graphics::Camera > camera;
	std::unique_ptr< CameraPresenter > controller;

};

	}
}