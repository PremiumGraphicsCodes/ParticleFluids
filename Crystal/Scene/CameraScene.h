#pragma once

#include "IScene.h"
#include "../Graphics/Camera.h"

#include "CameraSceneController.h"

namespace Crystal {
	namespace Scene {

class CameraScene : public IScene
{
public:
	CameraScene(const int id, const std::string& name, Graphics::Camera* camera) :
		IScene(id, name),
		camera(camera),
		controller(this)
	{}

	~CameraScene() {};

	Graphics::Camera* getCamera() const { return camera.get(); }

	CameraSceneController getController() { return controller; }

private:
	std::unique_ptr< Graphics::Camera > camera;
	CameraSceneController controller;

};

	}
}