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

class ObjectIdViewModel
{
public:
	void add(Model::Scene& objects);

	Graphics::PointBuffer getPointIdBuffer() const { return pointIdBuffer; }

	Graphics::LineBuffer getLindIdBuffer() const { return lineIdBuffer; }

	Graphics::LineBuffer getTriangleIdBuffer() const { return triangleIdBuffer; }

private:
	void add(const Math::Vector3df& pos, const Graphics::ColorRGBAf& c, const float size);

	void add(const Model::ParticleSystemScene& object);

	void add(const Model::WireFrameScene& object);

	void add(const Model::PolygonMeshScene& object);

	Graphics::PointBuffer pointIdBuffer;
	Graphics::LineBuffer lineIdBuffer;
	Graphics::LineBuffer triangleIdBuffer;
};

	}
}