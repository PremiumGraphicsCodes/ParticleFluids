#pragma once

#include "../Graphics/PointBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/TriangleBuffer.h"
#include "../Graphics/LightBuffer.h"
#include "../Graphics/MaterialBuffer.h"
#include "ParticleSystemObject.h"
#include "WireFrameObject.h"
#include "PolygonMeshObject.h"
#include "LightObjectRepository.h"
#include "ObjectRepository.h"
#include "MaterialObjectRepository.h"

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

	void add(const PolygonMeshObject& object);

	Graphics::PointBuffer pointIdBuffer;
};

	}
}