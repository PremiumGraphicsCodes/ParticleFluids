#pragma once

#include "IRenderer.h"

#include "../Graphics/Camera.h"
#include "../Shader/ShaderObject.h"
#include "../Shader/VertexBufferObject.h"

namespace Crystal {
	namespace Scene {

class PointBuffer
{
public:
	PointBuffer() :
		matrix(Math::Identity())
	{};

	void add(const Math::Vector3df& position, const Graphics::ColorRGBAf& color, const float size) {
		this->position.add(position);
		this->color.add(color);
		this->sizes.add(size);
	}

	void add(const Math::Vector3dd& position, const Graphics::ColorRGBAf& color, const float size) {
		this->position.add(position);
		this->color.add(color);
		this->sizes.add(size);
	}

	void setMatrix(const Math::Matrix4dd& matrix) { this->matrix = matrix; }

	Math::Matrix4dd getMatrix() const { return matrix; }

	Graphics::Buffer3d<float> getPosition() const { return position; }

	Graphics::Buffer4d<float> getColor() const { return color; }

	Graphics::Buffer1d<float> getSize() const { return sizes; }

private:
	Math::Matrix4dd matrix;
	Graphics::Buffer3d<float> position;
	Graphics::Buffer4d<float> color;
	Graphics::Buffer1d<float> sizes;
};


class PointRenderer : public IRenderer
{
public:
	PointRenderer();

	bool build(Shader::GLObjectFactory& factory) override;

	void send(const PointBuffer& buffer);

	void render(const Graphics::Camera& camera) override;

private:
	std::string getBuiltInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	GLuint count;
	PointBuffer buffer;
	Shader::VertexBufferObject vertex_vbo;
	Shader::VertexBufferObject size_vbo;
	Shader::VertexBufferObject color_vbo;
	GLuint vao;
};

	}
}