#pragma once

#include "IShaderScene.h"
#include "TriangleBuffer.h"
#include "../Shader/VertexBufferObject.h"

#include <string>

namespace Crystal {
	namespace Scene {
		class TriangleShader;
		class CameraShaderScene;

class TriangleShaderScene : public IShaderScene
{
public:
	struct VBO {
		Shader::VertexBufferObject position;
		Shader::VertexBufferObject color;
	};
	VBO vbo;
	std::vector<unsigned int> indices;

	explicit TriangleShaderScene(const std::string& name) :
		IShaderScene(name)
	{}

	bool build(Shader::GLObjectFactory& glFactory) override;

	void release(Shader::GLObjectFactory& glFactory) override;

	void send(const TriangleBuffer& buffer);

	void setShader(TriangleShader* shader);

	void setCamera(CameraShaderScene* camera) { this->camera = camera; }

	void render() override;

	CameraShaderScene* getCamera() const { return camera; }

private:
	std::string name;
	TriangleShader* shader;
	CameraShaderScene* camera;
};

	}
}