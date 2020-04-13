#pragma once

#include "../Graphics/Camera.h"
#include "IShaderScene.h"

namespace Crystal {
	namespace Scene {

class CameraShaderScene : public IShaderScene
{
public:
	bool build(Shader::GLObjectFactory& glFactory) { return true; }

	void release(Shader::GLObjectFactory& glFactory) {}

	void render() {}

	void update(const Graphics::Camera& camera)
	{
		this->projectionMatrix = camera.getProjectionMatrix();
		this->modelViewMatrix = camera.getModelViewMatrix();
	}

	Math::Matrix4df getProjectionMatrix() const { return projectionMatrix; }

	Math::Matrix4df getModelViewMatrix() const { return modelViewMatrix; }

private:
	Math::Matrix4df projectionMatrix;
	Math::Matrix4df modelViewMatrix;
};
	}
}