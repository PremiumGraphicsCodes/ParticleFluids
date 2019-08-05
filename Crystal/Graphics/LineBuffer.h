#ifndef __CRYSTAL_GRAPHICS_LINE_BUFFER_H__
#define __CRYSTAL_GRAPHICS_LINE_BUFFER_H__

#include "Buffer3d.h"
#include "Buffer1d.h"
#include "Buffer4d.h"

namespace Crystal {
	namespace Graphics {

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

	void add(const Math::Vector3df& position, const ColorRGBAf& color, const int index) {
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

	}
}

#endif