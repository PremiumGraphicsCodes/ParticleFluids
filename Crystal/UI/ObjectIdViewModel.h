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

class ObjectIdViewModel
{
public:
	void add(Model::ObjectRepository& objects);

	Graphics::PointBuffer getPointIdBuffer() const { return pointIdBuffer; }

	Graphics::LineBuffer getLindIdBuffer() const { return lineIdBuffer; }

	Graphics::LineBuffer getTriangleIdBuffer() const { return triangleIdBuffer; }

private:
	void add(const Math::Vector3df& pos, const Graphics::ColorRGBAf& c, const float size);

	void add(const Model::ParticleSystemObject& object);

	void add(const Model::WireFrameObject& object);

	void add(const Model::PolygonMeshObject& object);

	Graphics::PointBuffer pointIdBuffer;
	Graphics::LineBuffer lineIdBuffer;
	Graphics::LineBuffer triangleIdBuffer;
};

	}
}