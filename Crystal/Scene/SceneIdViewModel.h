#pragma once

#include "../Graphics/PointBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/TriangleBuffer.h"
#include "../Graphics/LightBuffer.h"
#include "../Graphics/MaterialBuffer.h"
#include "../Scene/ParticleSystemScene.h"
#include "../Scene/WireFrameScene.h"
#include "../Scene/PolygonMeshScene.h"
#include "../Scene/Scene.h"

namespace Crystal {
	namespace UI {

class SceneIdViewModel
{
public:
	Graphics::PointBuffer getPointIdBuffer() const { return pointIdBuffer; }

	Graphics::LineBuffer getLindIdBuffer() const { return lineIdBuffer; }

	Graphics::LineBuffer getTriangleIdBuffer() const { return triangleIdBuffer; }

private:

	void add(const Model::PolygonMeshScene& object);

public:
	Graphics::PointBuffer pointIdBuffer;
	Graphics::LineBuffer lineIdBuffer;
	Graphics::LineBuffer triangleIdBuffer;
};

	}
}