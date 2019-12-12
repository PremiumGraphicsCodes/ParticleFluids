#pragma once

#include "IRenderer.h"

#include "../Graphics/Camera.h"
#include "../Shader/ShaderObject.h"

namespace Crystal {
	namespace Scene {

class PointBuffer
{
public:
	PointBuffer() {};

	void clear() {
		position.clear();
		color.clear();
		sizes.clear();
	}

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

	Graphics::Buffer3d<float> getPosition() const { return position; }

	Graphics::Buffer4d<float> getColor() const { return color; }

	Graphics::Buffer1d<float> getSize() const { return sizes; }

private:
	Graphics::Buffer3d<float> position;
	Graphics::Buffer4d<float> color;
	Graphics::Buffer1d<float> sizes;
};


class PointRenderer : public IRenderer
{
public:
	PointRenderer();

	void render(const Graphics::Camera& camera) override;

	void setBuffer(const PointBuffer& buffer) { this->buffer = buffer; }

private:
	std::string getBuiltInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	PointBuffer buffer;
};

	}
}