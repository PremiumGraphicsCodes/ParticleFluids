#pragma once

#include "PointShaderScene.h"
#include "LineShaderScene.h"

namespace Crystal {
	namespace Scene {

class SceneIdViewModel
{
public:
	PointBuffer getPointIdBuffer() const { return pointIdBuffer; }

	LineBuffer getLindIdBuffer() const { return lineIdBuffer; }

	LineBuffer getTriangleIdBuffer() const { return triangleIdBuffer; }

public:
	PointBuffer pointIdBuffer;
	LineBuffer lineIdBuffer;
	LineBuffer triangleIdBuffer;
};

	}
}