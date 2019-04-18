#pragma once

#include "../Graphics/PointBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/TriangleBuffer.h"
#include "../Graphics/LightBuffer.h"
#include "../Graphics/MaterialBuffer.h"
#include "../Model/ParticleSystemObject.h"
#include "../Model/WireFrameObject.h"
#include "../Model/PolygonMeshObject.h"
#include "../Model/LightObjectRepository.h"
#include "../Model/ObjectRepository.h"
#include "../Model/MaterialObjectRepository.h"

namespace Crystal {
	namespace UI {
		class AppearanceObjectRepository;

class ObjectIdViewModel
{
public:
	void add(ObjectRepository& objects);

	Graphics::PointBuffer getPointIdBuffer() const { return pointIdBuffer; }

private:
	void add(const Math::Vector3df& pos, const Graphics::ColorRGBAf& c, const float size);

	void add(const ParticleSystemObject& object);

	void add(const WireFrameObject& object);

	void add(const PolygonMeshObject& object);

	Graphics::PointBuffer pointIdBuffer;
	Graphics::LineBuffer lineIdBuffer;
	Graphics::TriangleBuffer triangleIdBuffer;
};

	}
}