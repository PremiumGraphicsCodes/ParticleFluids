#pragma once

#include "SceneIdProvider.h"
#include "PolygonMeshScene.h"
#include "ParticleSystemScene.h"
#include "WireFrameScene.h"
#include "LightScene.h"
#include "MaterialScene.h"

namespace Crystal {
	namespace Model {

class SceneFactory
{
public:
	explicit SceneFactory(SceneIdProvider& idProvider);

	~SceneFactory();

	void clear();

	ParticleSystemScene* addParticleSystemScene(const Math::Vector3dd& position, const ParticleAttribute& attribute, const std::string& name);

	ParticleSystemScene* addParticleSystemScene(const std::vector<Math::Vector3dd>& positions, const ParticleAttribute& attribute, const std::string& name);

	ParticleSystemScene* addParticleSystemScene(const std::vector<Math::Vector3dd>& positions, const std::vector<ParticleAttribute>& attributes, const std::string& name);

	int addWireFrameScene(Shape::WireFrame* wire, const WireFrameAttribute& attribute, const std::string& name);

	int addPolygonMeshScene(Shape::PolygonMesh* mesh, Graphics::Material* material, const std::string& name);

	void addLightScene(Graphics::PointLight* l, const std::string& name);

	int addMaterialScene(Graphics::Material* m, const std::string& name);

	std::list<WireFrameScene*> getWireFrames() const { return wires; }

	std::list<PolygonMeshScene*> getPolygonMeshes() const { return polygonMeshes; }

	std::vector<LightScene*> getLights() const { return lights; }

	Math::Box3d getBoundingBox() const;

	std::list<Math::Vector3dd> getAllVertices() const;

	int getNextId() { return idProvider.getNextId(); }

private:
	SceneIdProvider& idProvider;
	std::list<WireFrameScene*> wires;
	std::list<PolygonMeshScene*> polygonMeshes;
	std::vector<LightScene*> lights;
	std::vector<MaterialScene*> materials;

};

	}
}