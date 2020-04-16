#pragma once

#include "../Math/Vector3d.h"
#include "../Math/Matrix4d.h"

#include "../Shader/VertexBufferObject.h"
#include "../Graphics/Camera.h"

#include "LineBuffer.h"

#include "IShaderScene.h"

namespace Crystal {
	namespace Scene {
		class LineShader;

class LineShaderScene : public IShaderScene
{
public:
	struct {
		Shader::VertexBufferObject position;
		Shader::VertexBufferObject color;
	} vbo;
	//Shader::VertexArrayObject vao;

	std::vector<unsigned int> indices;
	Math::Matrix4df matrix;
	Graphics::Camera camera;
	float lineWidth;

	LineShaderScene() {}

	explicit LineShaderScene(const std::string& name) :
		IShaderScene(name)
	{}

	bool build(Shader::GLObjectFactory& glFactory) override;

	void release(Shader::GLObjectFactory& glFactory) override;

	void render() override;

	void send(const LineBuffer& buffer);

	void setShader(LineShader* shader) { this->shader = shader; }

private:
	LineShader* shader;
};

	}
}