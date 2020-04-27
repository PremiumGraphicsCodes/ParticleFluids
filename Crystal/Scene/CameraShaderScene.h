#pragma once

#include "../Graphics/Camera.h"
#include "IShaderScene.h"

namespace Crystal {
	namespace Scene {

class CameraShaderScene : public IShaderScene
{
public:
	explicit CameraShaderScene(const std::string& name);

	bool build(Shader::GLObjectFactory& glFactory) { return true; }

	void release(Shader::GLObjectFactory& glFactory) {}

	void render() {}

	void update(const Graphics::Camera& camera);

	Math::Matrix4df getProjectionMatrix() const { return projectionMatrix; }

	Math::Matrix4df getModelViewMatrix() const { return modelViewMatrix; }

	Math::Vector3df getEyePosition() const { return eyePosition; }

private:
	Math::Matrix4df projectionMatrix;
	Math::Matrix4df modelViewMatrix;
	Math::Vector3df eyePosition;
};
	}
}