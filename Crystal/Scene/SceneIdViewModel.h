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

	std::list<Graphics::LineBuffer> getTriangleIdBuffer() const { return triangleIdBuffers; }

	void merge(SceneIdViewModel& rhs) {
		pointIdBuffer.merge(rhs.pointIdBuffer);
		lineIdBuffer.merge(rhs.lineIdBuffer);
		triangleIdBuffers.splice(triangleIdBuffers.end(), rhs.triangleIdBuffers);
	}


public:
	Graphics::PointBuffer pointIdBuffer;
	Graphics::LineBuffer lineIdBuffer;
	std::list<Graphics::LineBuffer> triangleIdBuffers;
};

	}
}