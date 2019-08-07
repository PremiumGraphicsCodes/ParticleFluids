#pragma once

#include "PointShaderScene.h"
#include "SmoothShaderScene.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/LightBuffer.h"
#include "../Graphics/MaterialBuffer.h"

namespace Crystal {
	namespace Scene {

class SceneViewModel
{
public:
	PointBuffer getPointBuffer() const { return pointBuffer; }

	Graphics::LineBuffer getLineBuffer() const { return lineBuffer; }

	std::list<SmoothTriangleBuffer> getTriangleBuffers() const { return triangleBuffers; }

	Graphics::LightBuffer getLightBuffers() const { return lightBuffer; }

	void merge(SceneViewModel& rhs) {
		pointBuffer.merge(rhs.pointBuffer);
		lineBuffer.merge(rhs.lineBuffer);
		lightBuffer.merge(rhs.lightBuffer);
		triangleBuffers.splice(triangleBuffers.end(), rhs.triangleBuffers);
	}

public:
	PointBuffer pointBuffer;
	Graphics::LineBuffer lineBuffer;
	std::list<SmoothTriangleBuffer> triangleBuffers;
	Graphics::LightBuffer lightBuffer;
	std::list<Graphics::MaterialBuffer> materialBuffers;
};

	}
}