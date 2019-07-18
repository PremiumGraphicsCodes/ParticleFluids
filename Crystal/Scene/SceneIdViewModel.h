#pragma once

#include "../Graphics/PointBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/TriangleBuffer.h"
#include "../Graphics/LightBuffer.h"
#include "../Graphics/MaterialBuffer.h"
#include "../Scene/ParticleSystemScene.h"
#include "../Scene/WireFrameScene.h"
#include "../Scene/PolygonMeshScene.h"

namespace Crystal {
	namespace Scene {

class SceneIdViewModel
{
public:
	std::list<Graphics::PointBuffer> getPointIdBuffers() const { return pointIdBuffers; }

	std::list<Graphics::LineBuffer> getLindIdBuffer() const { return lineIdBuffers; }

	std::list<Graphics::LineBuffer> getTriangleIdBuffer() const { return triangleIdBuffers; }

	void merge(SceneIdViewModel& rhs) {
		pointIdBuffers.splice(pointIdBuffers.end(), rhs.pointIdBuffers);
		lineIdBuffers.splice(lineIdBuffers.end(), rhs.lineIdBuffers);
		triangleIdBuffers.splice(triangleIdBuffers.end(), rhs.triangleIdBuffers);
	}


public:
	std::list<Graphics::PointBuffer> pointIdBuffers;
	std::list<Graphics::LineBuffer> lineIdBuffers;
	std::list<Graphics::LineBuffer> triangleIdBuffers;
};

	}
}