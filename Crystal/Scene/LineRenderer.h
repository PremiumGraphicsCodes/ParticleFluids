#pragma once

#include "IRenderer.h"

#include "../Shader/ShaderObject.h"

#include "../Graphics/ICamera.h"
#include "../Graphics/Buffer1d.h"
#include "../Graphics/Buffer3d.h"
#include "../Graphics/Buffer4d.h"

namespace Crystal {
	namespace Scene {

class LineBuffer
{
public:
	LineBuffer() :
		width(1.0f)
	{}

	explicit LineBuffer(const float width) :
		width(width)
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

private:
	float width;
	Graphics::Buffer3d<float> positions;
	Graphics::Buffer4d<float> colors;
	Graphics::Buffer1d<unsigned int> indices;
};


class LineRenderer : public IRenderer
{
public:
	LineRenderer(const int id, const std::string& name);

	void render(const Graphics::ICamera& camera) override;

	void setBuffer(const LineBuffer& buffer) {
		this->buffer = buffer;
	}

private:
	std::string getBuiltInVsSource() const;

	std::string getBuiltInFsSource() const;

	LineBuffer buffer;
};

	}
}