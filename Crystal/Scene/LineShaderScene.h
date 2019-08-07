#pragma once

#include "ShaderScene.h"

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
	LineBuffer() {};

	~LineBuffer()
	{

	}

	void clear() {
		indices.clear();
		positions.clear();
		colors.clear();
	}

	void add(const Math::Vector3df& position, const Graphics::ColorRGBAf& color, const int index) {
		positions.add(position);
		colors.add(color);
		indices.add(index);
	}

	Graphics::Buffer3d<float> getPositions() const { return positions; }

	Graphics::Buffer4d<float> getColors() const { return colors; }

	Graphics::Buffer1d<unsigned int> getIndices() const { return indices; }

	void merge(LineBuffer& rhs)
	{
		this->positions.merge(rhs.positions);
		this->colors.add(rhs.colors);
		this->indices.merge(rhs.indices);
	}

private:
	Graphics::Buffer3d<float> positions;
	Graphics::Buffer4d<float> colors;
	Graphics::Buffer1d<unsigned int> indices;
};


class LineShaderScene : public ShaderScene
{
public:
	LineShaderScene(const int id, const std::string& name);

	void render(const Graphics::ICamera& camera) override;

	void setBuffer(const LineBuffer& buffer, const float width) {
		this->buffer = buffer;
		this->width = width;
	}

private:
	std::string getBuiltInVsSource() const;

	std::string getBuiltInFsSource() const;

	LineBuffer buffer;
	float width;
};

	}
}