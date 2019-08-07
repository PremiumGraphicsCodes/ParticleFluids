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
	std::list<PointBuffer> getPointBuffers() const { return pointBuffers; }

	std::list<Graphics::LineBuffer> getLineBuffers() const { return lineBuffers; }

	std::list<SmoothTriangleBuffer> getTriangleBuffers() const { return triangleBuffers; }

	Graphics::LightBuffer getLightBuffers() const { return lightBuffer; }

	void merge(SceneViewModel& rhs) {
		pointBuffers.splice(pointBuffers.end(), rhs.pointBuffers);
		lineBuffers.splice(lineBuffers.end(), rhs.lineBuffers);
		lightBuffer.merge(rhs.lightBuffer);
		triangleBuffers.splice(triangleBuffers.end(), rhs.triangleBuffers);
	}

public:
	std::list<PointBuffer> pointBuffers;
	std::list<Graphics::LineBuffer> lineBuffers;
	std::list<SmoothTriangleBuffer> triangleBuffers;
	Graphics::LightBuffer lightBuffer;
	std::list<Graphics::MaterialBuffer> materialBuffers;
};

	}
}