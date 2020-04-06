#pragma once

#include "IScene.h"
#include "../Graphics/ColorRGBA.h"
#include "../Graphics/Camera.h"

namespace Crystal {
	namespace Scene {

class CameraScene : public IScene
{
public:
	CameraScene(const int id, const std::string& name, Graphics::Camera* camera) :
		IScene(id, name),
		camera(camera)
	{}

	~CameraScene() {};

	Graphics::Camera* getCamera() const { return camera.get(); }

private:
	std::unique_ptr< Graphics::Camera > camera;
};

	}
}