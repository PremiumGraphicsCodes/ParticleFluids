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

	std::list<Graphics::LineBuffer> getLindIdBuffer() const { return lineIdBuffers; }

	std::list<Graphics::LineBuffer> getTriangleIdBuffer() const { return triangleIdBuffers; }

	void merge(SceneIdViewModel& rhs) {
		pointIdBuffer.merge(rhs.pointIdBuffer);
		lineIdBuffers.splice(lineIdBuffers.end(), rhs.lineIdBuffers);
		triangleIdBuffers.splice(triangleIdBuffers.end(), rhs.triangleIdBuffers);
	}


public:
	Graphics::PointBuffer pointIdBuffer;
	std::list<Graphics::LineBuffer> lineIdBuffers;
	std::list<Graphics::LineBuffer> triangleIdBuffers;
};

	}
}