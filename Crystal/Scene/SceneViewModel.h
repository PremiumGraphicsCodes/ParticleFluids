#pragma once

#include "PointRenderer.h"
#include "LineRenderer.h"
#include "SmoothRenderer.h"
#include "../Graphics/PointLight.h"
#include "../Graphics/Material.h"

namespace Crystal {
	namespace Scene {

class SceneViewModel
{
public:
	std::list<PointBuffer> getPointBuffers() const { return pointBuffers; }

	std::list<LineBuffer> getLineBuffers() const { return lineBuffers; }

	std::list<SmoothTriangleBuffer> getTriangleBuffers() const { return triangleBuffers; }

	std::vector<Graphics::PointLight> getLights() const { return lights; }

	std::vector<Graphics::Material> getMaterials() const { return materials; }

public:
	std::list<PointBuffer> pointBuffers;
	std::list<LineBuffer> lineBuffers;
	std::list<SmoothTriangleBuffer> triangleBuffers;
	std::vector<Graphics::PointLight> lights;
	std::vector<Graphics::Material> materials;
};

	}
}