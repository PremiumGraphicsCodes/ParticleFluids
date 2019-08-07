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

	void merge(SceneIdViewModel& rhs) {
		pointIdBuffer.merge(rhs.pointIdBuffer);
		lineIdBuffer.merge(rhs.lineIdBuffer);
		triangleIdBuffer.merge(triangleIdBuffer);
	}

public:
	PointBuffer pointIdBuffer;
	LineBuffer lineIdBuffer;
	LineBuffer triangleIdBuffer;
};

	}
}