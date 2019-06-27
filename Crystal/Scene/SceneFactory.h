#pragma once

#include "IObjectRepository.h"
#include "PolygonMeshScene.h"
#include "ParticleSystemScene.h"
#include "WireFrameScene.h"
#include "PolygonMeshAttribute.h"

namespace Crystal {
	namespace Model {

class SceneFactory : public IObjectRepository
{
public:
	explicit SceneFactory(SceneIdProvider& idProvider) :
		IObjectRepository(idProvider)
	{}

	~SceneFactory();

	void clear();

	int addParticleSystemScene(const Math::Vector3dd& position, const ParticleAttribute& attribute, const std::string& name);

	int addParticleSystemScene(const std::vector<Math::Vector3dd>& positions, const ParticleAttribute& attribute, const std::string& name);

	int addParticleSystemScene(const std::vector<Math::Vector3dd>& positions, const std::vector<ParticleAttribute>& attributes, const std::string& name);

	int addWireFrameScene(Shape::WireFrame* wire, const WireFrameAttribute& attribute, const std::string& name);

	int addPolygonMeshScene(Shape::PolygonMesh* mesh, const std::string& name);

	PolygonMeshScene* findObjectById(const int id) const;

	std::list<ParticleSystemScene*> getParticleSystems() const { return particleSystemScenes; }

	std::list<WireFrameScene*> getWires() const { return wires; }

	std::list<PolygonMeshScene*> getObjects() const { return polygonMeshes; }

	Math::Box3d getBoundingBox() const override;

	std::list<Math::Vector3dd> getAllVertices() const override;

private:
	std::list<ParticleSystemScene*> particleSystemScenes;
	std::list<WireFrameScene*> wires;
	std::list<PolygonMeshScene*> polygonMeshes;

};

	}
}