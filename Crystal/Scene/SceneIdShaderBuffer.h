#pragma once

#include "PointShader.h"
#include "LineShader.h"

namespace Crystal {
	namespace Scene {

class ScreenIdShaderBuffer
{
public:
	std::vector<PointBuffer> pointIdBuffers;
	std::vector<LineBuffer> lineIdBuffers;
	std::vector<LineBuffer> triangleIdBuffers;
};

	}
}