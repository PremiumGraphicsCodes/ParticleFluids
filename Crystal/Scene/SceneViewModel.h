#pragma once

#include "PointShaderScene.h"
#include "LineShaderScene.h"
#include "SmoothShaderScene.h"
#include "../Graphics/PointLight.h"
#include "MaterialShaderScene.h"

namespace Crystal {
	namespace Scene {

class SceneViewModel
{
public:
	std::list<PointBuffer> getPointBuffers() const { return pointBuffers; }

	std::list<LineBuffer> getLineBuffers() const { return lineBuffers; }

	std::list<SmoothTriangleBuffer> getTriangleBuffers() const { return triangleBuffers; }

	std::list<Graphics::PointLight> getLights() const { return lights; }

	void merge(SceneViewModel& rhs) {
		pointBuffers.splice(pointBuffers.end(), rhs.pointBuffers);
		lineBuffers.splice(lineBuffers.end(), rhs.lineBuffers);
		lights.splice(lights.end(), rhs.lights);
		triangleBuffers.splice(triangleBuffers.end(), rhs.triangleBuffers);
	}

public:
	std::list<PointBuffer> pointBuffers;
	std::list<LineBuffer> lineBuffers;
	std::list<SmoothTriangleBuffer> triangleBuffers;
	std::list<Graphics::PointLight> lights;
	std::list<MaterialBuffer> materialBuffers;
};

	}
}