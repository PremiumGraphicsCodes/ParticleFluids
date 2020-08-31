#pragma once

#include "../Math/Vector3d.h"
#include "../Math/Matrix4d.h"

#include "../Shader/VertexBufferObject.h"
#include "../Graphics/Camera.h"

#include "LineBuffer.h"
#include "../Shader/LineRenderer.h"

#include "IShaderScene.h"
#include "CameraShaderScene.h"


namespace Crystal {
	namespace Scene {
		class CameraShaderScene;

class LineShaderScene : public IShaderScene
{
public:
	explicit LineShaderScene(const std::string& name);

	bool build(Shader::GLObjectFactory& glFactory) override;

	void release(Shader::GLObjectFactory& glFactory) override;

	void render() override;

	void send(const LineBuffer& buffer);

	void setShader(Shader::LineRenderer* shader) { this->shader = shader; }

	void setCamera(CameraShaderScene* camera) { this->camera = camera; }

	CameraShaderScene* getCamera() const { return camera; }

private:
	Shader::LineRenderer* shader;
	Shader::LineRenderer::Buffer sBuffer;
	CameraShaderScene* camera;
};

	}
}