#pragma once

#include "IShaderScene.h"
#include "TriangleBuffer.h"
#include "../Shader/TriangleRenderer.h"
#include "../Shader/VertexBufferObject.h"

#include <string>

namespace Crystal {
	namespace Scene {
		class TriangleShader;
		class CameraShaderScene;

class TriangleShaderScene : public IShaderScene
{
public:
	explicit TriangleShaderScene(const std::string& name) :
		IShaderScene(name)
	{}

	bool build(Shader::GLObjectFactory& glFactory) override;

	void release(Shader::GLObjectFactory& glFactory) override;

	void send(const TriangleBuffer& buffer);

	void setShader(Shader::TriangleRenderer* shader);

	void setCamera(CameraShaderScene* camera) { this->camera = camera; }

	void render() override;

	CameraShaderScene* getCamera() const { return camera; }

private:
	std::string name;
	Shader::TriangleRenderer* shader;
	Shader::TriangleRenderer::Buffer sBuffer;
	CameraShaderScene* camera;
};

	}
}