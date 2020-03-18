#pragma once

#include "PointRenderer.h"
#include "LineShaderScene.h"

namespace Crystal {
	namespace Scene {

class SceneIdViewModel
{
public:
	std::vector<PointBuffer> pointIdBuffers;
	std::vector<LineBuffer> lineIdBuffers;
	std::vector<LineBuffer> triangleIdBuffers;
};

	}
}