#pragma once

#include "PointShader.h"
#include "LineShader.h"

namespace Crystal {
	namespace Scene {
		class ParticleSystemScene;
		class WireFrameScene;
		class PolygonMeshScene;

class ScreenIdShaderScene
{
public:
	void add(ParticleSystemScene* scene);

	void add(WireFrameScene* scene);

	void add(PolygonMeshScene* scene);

	std::vector<PointBuffer> pointIdBuffers;
	std::vector<LineBuffer> lineIdBuffers;
	std::vector<LineBuffer> triangleIdBuffers;
};

	}
}