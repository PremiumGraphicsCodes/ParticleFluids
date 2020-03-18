#pragma once

#include "../Math/Vector3d.h"
#include "../Math/Matrix4d.h"
#include "../Graphics/ColorRGBA.h"
#include "../Graphics/Buffer1d.h"
#include "../Graphics/Buffer3d.h"
#include "../Graphics/Buffer4d.h"
#include "../Shader/VertexBufferObject.h"
#include "../Shader/VertexArrayObject.h"


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

struct PointShaderBuffer
{
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

	void build();

	void release();

	void send(const PointBuffer& buffer);
};

	}
}