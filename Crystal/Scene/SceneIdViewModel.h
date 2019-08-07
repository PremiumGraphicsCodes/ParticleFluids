#pragma once

#include "PointShaderScene.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/LightBuffer.h"
#include "../Graphics/MaterialBuffer.h"

namespace Crystal {
	namespace Scene {

class SceneIdViewModel
{
public:
	PointBuffer getPointIdBuffer() const { return pointIdBuffer; }

	Graphics::LineBuffer getLindIdBuffer() const { return lineIdBuffer; }

	Graphics::LineBuffer getTriangleIdBuffer() const { return triangleIdBuffer; }

	void merge(SceneIdViewModel& rhs) {
		pointIdBuffer.merge(rhs.pointIdBuffer);
		lineIdBuffer.merge(rhs.lineIdBuffer);
		triangleIdBuffer.merge(triangleIdBuffer);
	}

public:
	PointBuffer pointIdBuffer;
	Graphics::LineBuffer lineIdBuffer;
	Graphics::LineBuffer triangleIdBuffer;
};

	}
}