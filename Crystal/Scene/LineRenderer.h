#pragma once

#include "IRenderer.h"

#include "../Shader/ShaderObject.h"

#include "../Graphics/Camera.h"
#include "../Graphics/Buffer1d.h"
#include "../Graphics/Buffer3d.h"
#include "../Graphics/Buffer4d.h"

#include "../Shader/VertexBufferObject.h"
#include "../Shader/VertexArrayObject.h"

namespace Crystal {
	namespace Scene {

class LineBuffer
{
public:
	LineBuffer() :
		width(1.0f),
		matrix(Math::Identity())
	{}

	explicit LineBuffer(const float width) :
		width(width),
		matrix(Math::Identity())
	{};

	void addVertex(const Math::Vector3df& position, const Graphics::ColorRGBAf& color) {
		positions.add(position);
		colors.add(color);
	}

	void addIndex(const int index) {
		indices.add(index);
	}

	float getWidth() const { return width; }

	Graphics::Buffer3d<float> getPositions() const { return positions; }

	Graphics::Buffer4d<float> getColors() const { return colors; }

	Graphics::Buffer1d<unsigned int> getIndices() const { return indices; }

	void setMatrix(const Math::Matrix4dd& matrix) { this->matrix = matrix; }

	Math::Matrix4dd getMatrix() const { return matrix; }

private:
	Math::Matrix4dd matrix;
	float width;
	Graphics::Buffer3d<float> positions;
	Graphics::Buffer4d<float> colors;
	Graphics::Buffer1d<unsigned int> indices;
};


class LineRenderer : public IRenderer
{
public:
	LineRenderer();

	bool build(Shader::GLObjectFactory& factory) override;

	void send(const LineBuffer& buffer);

	void render(const Graphics::Camera& camera) override;

private:
	std::string getBuiltInVsSource() const;

	std::string getBuiltInFsSource() const;

	Shader::VertexBufferObject vertex_vbo;
	Shader::VertexBufferObject color_vbo;
	Shader::VertexArrayObject vao;
	std::vector<unsigned int> indices;
	Math::Matrix4df matrix;
	float lineWidth;
};

	}
}