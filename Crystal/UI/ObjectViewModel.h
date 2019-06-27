#pragma once

#include "../Graphics/PointBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/TriangleBuffer.h"
#include "../Scene/ParticleSystemScene.h"
#include "../Scene/WireFrameScene.h"
#include "../Scene/PolygonMeshObject.h"
#include "../Scene/ObjectRepository.h"
#include "../Scene/MaterialObjectRepository.h"

namespace Crystal {
	namespace UI {

class ObjectViewModel
{
public:
	void add(Model::ObjectRepository& objects, Model::MaterialObjectRepository& materials);

	Graphics::PointBuffer getPointBuffer() const { return pointBuffer; }

	Graphics::LineBuffer getLineBuffer() const { return lineBuffer; }

	std::vector<Graphics::TriangleBuffer> getTriangleBuffers() const { return triangleBuffers; }

private:
	void add(const Math::Vector3df& pos, const Graphics::ColorRGBAf& c, const float size);

	void add(const Model::ParticleSystemScene& object);

	void add(const Model::WireFrameScene& object);

	void add(const Model::PolygonMeshObject& object, Model::MaterialObjectRepository& materials);

	Graphics::PointBuffer pointBuffer;
	Graphics::LineBuffer lineBuffer;
	std::vector<Graphics::TriangleBuffer> triangleBuffers;
};

	}
}