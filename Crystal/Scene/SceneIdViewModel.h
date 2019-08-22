#pragma once

#include "PointRenderer.h"
#include "LineRenderer.h"

namespace Crystal {
	namespace Scene {

class SceneIdViewModel
{
public:
	std::vector<PointBuffer> getPointIdBuffers() const { return pointIdBuffers; }

	std::vector<LineBuffer> getLindIdBuffers() const { return lineIdBuffers; }

	std::vector<LineBuffer> getTriangleIdBuffers() const { return triangleIdBuffers; }

public:
	std::vector<PointBuffer> pointIdBuffers;
	std::vector<LineBuffer> lineIdBuffers;
	std::vector<LineBuffer> triangleIdBuffers;
};

	}
}