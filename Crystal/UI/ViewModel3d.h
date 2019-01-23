#pragma once

#include "../Graphics/PointBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/TriangleBuffer.h"
#include "../Graphics/LightBuffer.h"
#include "../Graphics/MaterialBuffer.h"
#include "ParticleSystemObject.h"
#include "WireFrameObject.h"
#include "PolygonMeshObject.h"
#include "LightRepository.h"
#include "ObjectRepository.h"
#include "MaterialRepository.h"

namespace Crystal {
	namespace UI {

class ViewModel3d
{
public:
	void add(const ObjectRepository& objects);

	void add(const LightRepository& lights);

	void add(const MaterialRepository& materials);

	Graphics::PointBuffer getPointBuffer() const { return pointBuffer; }

	Graphics::LineBuffer getLineBuffer() const { return lineBuffer; }

	Graphics::TriangleBuffer getTriangleBuffer() const { return triangleBuffer; }

	Graphics::LightBuffer getLightBuffer() const { return lightBuffer; }

	Graphics::MaterialBuffer getMaterialBuffer() const { return materialBuffer; }

private:
	void add(const Math::Vector3df& pos, const Graphics::ColorRGBAf& c, const float size);

	void add(const ParticleSystemObject& object);

	void add(const WireFrameObject& object);

	void add(const PolygonMeshObject& object);

	Graphics::PointBuffer pointBuffer;
	Graphics::LineBuffer lineBuffer;
	Graphics::TriangleBuffer triangleBuffer;
	Graphics::LightBuffer lightBuffer;
	Graphics::MaterialBuffer materialBuffer;
};

	}
}