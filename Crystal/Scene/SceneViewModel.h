#pragma once

#include "../Graphics/PointBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/TriangleBuffer.h"
#include "../Graphics/LightBuffer.h"
#include "../Graphics/MaterialBuffer.h"

namespace Crystal {
	namespace UI {

class SceneViewModel
{
public:
	Graphics::PointBuffer getPointBuffer() const { return pointBuffer; }

	Graphics::LineBuffer getLineBuffer() const { return lineBuffer; }

	std::vector<Graphics::TriangleBuffer> getTriangleBuffers() const { return triangleBuffers; }

	Graphics::LightBuffer getLightBuffer() const { return lightBuffer; }

public:
	Graphics::PointBuffer pointBuffer;
	Graphics::LineBuffer lineBuffer;
	std::vector<Graphics::TriangleBuffer> triangleBuffers;
	Graphics::LightBuffer lightBuffer;
	Graphics::MaterialBuffer materialBuffer;
};

	}
}