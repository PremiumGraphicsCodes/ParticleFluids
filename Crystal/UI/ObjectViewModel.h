#pragma once

#include "../Graphics/PointBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/TriangleBuffer.h"
#include "../Model/ParticleSystemObject.h"
#include "../Model/WireFrameObject.h"
#include "../Model/PolygonMeshObject.h"
#include "../Model/ObjectRepository.h"
#include "../Model/MaterialObjectRepository.h"

namespace Crystal {
	namespace UI {

class ObjectViewModel
{
public:
	void add(ObjectRepository& objects, MaterialObjectRepository& materials);

	Graphics::PointBuffer getPointBuffer() const { return pointBuffer; }

	Graphics::LineBuffer getLineBuffer() const { return lineBuffer; }

	std::vector<Graphics::TriangleBuffer> getTriangleBuffers() const { return triangleBuffers; }

private:
	void add(const Math::Vector3df& pos, const Graphics::ColorRGBAf& c, const float size);

	void add(const ParticleSystemObject& object);

	void add(const WireFrameObject& object);

	void add(const PolygonMeshObject& object, MaterialObjectRepository& materials);

	Graphics::PointBuffer pointBuffer;
	Graphics::LineBuffer lineBuffer;
	std::vector<Graphics::TriangleBuffer> triangleBuffers;
};

	}
}