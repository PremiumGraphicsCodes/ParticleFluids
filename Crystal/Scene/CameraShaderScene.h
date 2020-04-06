#pragma once

#include "../Graphics/Camera.h"

namespace Crystal {
	namespace Shader {

class CameraShaderScene
{
public:
	CameraShaderScene(Graphics::Camera* camera);

	Graphics::Camera* getCamera() { return camera; }

private:
	Graphics::Camera* camera;
};
	}
}