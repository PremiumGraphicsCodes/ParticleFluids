#pragma once

#include "../Util/UnCopyable.h"
#include "ParticleSystemObjectRepository.h"
#include "SceneFactory.h"
#include "WireFrameObjectRepository.h"

namespace Crystal {
	namespace Model {

class Scene : private UnCopyable
{
public:
	Scene();

	~Scene();

	void clear();

	ParticleSystemObjectRepository* getParticleSystems() { return &particleSystems; }

	WireFrameObjectRepository* getWireFrames() { return &wireFrames; }

	SceneFactory* getPolygonMeshes() { return &polygonMeshes; }

	Math::Box3d getBoundingBox() const;

	std::list<Math::Vector3dd> getAllVertices() const;

	std::list<IScene*> getAllObjects() const;

	IScene* findObjectById(const int id);

	void add(IScene* scene) { children.push_back(scene); }

private:
	std::list<IScene*> children;

private:
	ObjectIdProvider idProvider;
	ParticleSystemObjectRepository particleSystems;
	WireFrameObjectRepository wireFrames;
	SceneFactory polygonMeshes;
};
	}
}