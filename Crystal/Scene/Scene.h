#pragma once

#include "../Util/UnCopyable.h"
#include "ParticleSystemObjectRepository.h"
#include "SceneFactory.h"

namespace Crystal {
	namespace Model {

class Scene : private UnCopyable
{
public:
	Scene();

	~Scene();

	void clear();

	ParticleSystemObjectRepository* getParticleSystems() { return &particleSystems; }

	SceneFactory* getFactory() { return &factory; }

	Math::Box3d getBoundingBox() const;

	std::list<Math::Vector3dd> getAllVertices() const;

	std::list<IScene*> getAllObjects() const;

	IScene* findObjectById(const int id);

	void add(IScene* scene) { children.push_back(scene); }

private:
	std::list<IScene*> children;

private:
	SceneIdProvider idProvider;
	ParticleSystemObjectRepository particleSystems;
	SceneFactory factory;
};
	}
}