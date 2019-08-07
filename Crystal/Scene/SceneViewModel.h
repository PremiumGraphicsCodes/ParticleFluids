#pragma once

#include "PointShaderScene.h"
#include "SmoothShaderScene.h"
#include "../Graphics/LineBuffer.h"
#include "../Scene/LightShaderScene.h"
#include "../Graphics/MaterialBuffer.h"

namespace Crystal {
	namespace Scene {

class SceneViewModel
{
public:
	std::list<PointBuffer> getPointBuffers() const { return pointBuffers; }

	std::list<Graphics::LineBuffer> getLineBuffers() const { return lineBuffers; }

	std::list<SmoothTriangleBuffer> getTriangleBuffers() const { return triangleBuffers; }

	std::list<LightBuffer> getLightBuffers() const { return lightBuffers; }

	void merge(SceneViewModel& rhs) {
		pointBuffers.splice(pointBuffers.end(), rhs.pointBuffers);
		lineBuffers.splice(lineBuffers.end(), rhs.lineBuffers);
		lightBuffers.splice(lightBuffers.end(), rhs.lightBuffers);
		triangleBuffers.splice(triangleBuffers.end(), rhs.triangleBuffers);
	}

public:
	std::list<PointBuffer> pointBuffers;
	std::list<Graphics::LineBuffer> lineBuffers;
	std::list<SmoothTriangleBuffer> triangleBuffers;
	std::list<LightBuffer> lightBuffers;
	std::list<Graphics::MaterialBuffer> materialBuffers;
};

	}
}