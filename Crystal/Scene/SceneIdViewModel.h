#pragma once

#include "../Graphics/PointBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/TriangleBuffer.h"
#include "../Graphics/LightBuffer.h"
#include "../Graphics/MaterialBuffer.h"

namespace Crystal {
	namespace Scene {

class SceneIdViewModel
{
public:
	Graphics::PointBuffer getPointIdBuffer() const { return pointIdBuffer; }

	Graphics::LineBuffer getLindIdBuffer() const { return lineIdBuffer; }

	Graphics::LineBuffer getTriangleIdBuffer() const { return triangleIdBuffer; }

	void merge(SceneIdViewModel& rhs) {
		pointIdBuffer.merge(rhs.pointIdBuffer);
		lineIdBuffer.merge(rhs.lineIdBuffer);
		triangleIdBuffer.merge(triangleIdBuffer);
	}

public:
	Graphics::PointBuffer pointIdBuffer;
	Graphics::LineBuffer lineIdBuffer;
	Graphics::LineBuffer triangleIdBuffer;
};

	}
}