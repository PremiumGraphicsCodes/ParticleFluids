#pragma once

#include "../Graphics/PointBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/TriangleBuffer.h"
#include "../Graphics/LightBuffer.h"
#include "../Graphics/MaterialBuffer.h"

namespace Crystal {
	namespace Scene {

class SceneViewModel
{
public:
	Graphics::PointBuffer getPointBuffer() const { return pointBuffer; }

	Graphics::LineBuffer getLineBuffer() const { return lineBuffer; }

	std::list<Graphics::TriangleBuffer> getTriangleBuffers() const { return triangleBuffers; }

	Graphics::LightBuffer getLightBuffers() const { return lightBuffer; }

	void merge(SceneViewModel& rhs) {
		pointBuffer.merge(rhs.pointBuffer);
		lineBuffer.merge(rhs.lineBuffer);
		triangleBuffers.splice(triangleBuffers.end(), rhs.triangleBuffers);
		lightBuffer.merge(rhs.lightBuffer);
	}

public:
	Graphics::PointBuffer pointBuffer;
	Graphics::LineBuffer lineBuffer;
	std::list<Graphics::TriangleBuffer> triangleBuffers;
	Graphics::LightBuffer lightBuffer;
	std::list<Graphics::MaterialBuffer> materialBuffers;
};

	}
}