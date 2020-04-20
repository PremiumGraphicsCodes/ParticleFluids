#pragma once

#include "IShaderScene.h"
#include "PointBuffer.h"
#include "../Shader/VertexBufferObject.h"
#include "../Shader/VertexArrayObject.h"
#include "../Graphics/Camera.h"
#include "CameraShaderScene.h"

namespace Crystal {
	namespace Scene {
		class PointShader;

class PointShaderScene : public IShaderScene
{
public:
	struct VBO
	{
		Shader::VertexBufferObject position;
		Shader::VertexBufferObject size;
		Shader::VertexBufferObject color;
	};

	//Shader::VertexArrayObject vao;
	VBO vbo;
	GLuint count;
	Math::Matrix4df matrix;

	explicit PointShaderScene(const std::string& name);

	bool build(Shader::GLObjectFactory& glFactory) override;

	void release(Shader::GLObjectFactory& glFactory) override;

	void render() override;

	void send(const PointBuffer& buffer);

	void setShader(PointShader* shader);

	void setCamera(CameraShaderScene* camera) { this->camera = camera; }

private:
	PointShader* shader;
	CameraShaderScene* camera;
};

	}
}