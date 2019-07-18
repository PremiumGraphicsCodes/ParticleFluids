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

	std::list<Graphics::LineBuffer> getLineBuffers() const { return lineBuffers; }

	std::list<Graphics::TriangleBuffer> getTriangleBuffers() const { return triangleBuffers; }

	std::list<Graphics::LightBuffer> getLightBuffers() const { return lightBuffers; }

	void merge(SceneViewModel& rhs) {
		pointBuffer.merge(rhs.pointBuffer);
		lineBuffers.splice(lineBuffers.end(), rhs.lineBuffers);
		triangleBuffers.splice(triangleBuffers.end(), rhs.triangleBuffers);
		lightBuffers.splice(lightBuffers.end(), rhs.lightBuffers);
	}

public:
	Graphics::PointBuffer pointBuffer;
	std::list<Graphics::LineBuffer> lineBuffers;
	std::list<Graphics::TriangleBuffer> triangleBuffers;
	std::list<Graphics::LightBuffer> lightBuffers;
	std::list<Graphics::MaterialBuffer> materialBuffers;
};

	}
}