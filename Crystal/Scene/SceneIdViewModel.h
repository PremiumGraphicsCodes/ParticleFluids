#pragma once

#include "PointRenderer.h"
#include "LineRenderer.h"

namespace Crystal {
	namespace Scene {

class SceneIdViewModel
{
public:
	PointBuffer getPointIdBuffer() const { return pointIdBuffer; }

	std::vector<LineBuffer> getLindIdBuffers() const { return lineIdBuffers; }

	LineBuffer getTriangleIdBuffer() const { return triangleIdBuffer; }

public:
	PointBuffer pointIdBuffer;
	std::vector<LineBuffer> lineIdBuffers;
	LineBuffer triangleIdBuffer;
};

	}
}