#pragma once

#include "../Util/UnCopyable.h"
#include "ParticleSystemObjectRepository.h"
#include "PolygonMeshObjectRepository.h"
#include "WireFrameObjectRepository.h"

namespace Crystal {
	namespace UI {

class ObjectRepository : private UnCopyable
{
public:
	ObjectRepository()
	{}

	~ObjectRepository();

	void clear();

	ParticleSystemObjectRepository* getParticleSystems() { return &particleSystems; }

	WireFrameObjectRepository* getWireFrames() { return &wireFrames; }

	PolygonMeshObjectRepository* getPolygonMeshes() { return &polygonMeshes; }

	Math::Box3d getBoundingBox() const;

	std::list<Math::Vector3dd> getAllVertices() const;

	std::list<IObject*> getAllObjects() const;

private:
	ParticleSystemObjectRepository particleSystems;
	WireFrameObjectRepository wireFrames;
	PolygonMeshObjectRepository polygonMeshes;
};
	}
}