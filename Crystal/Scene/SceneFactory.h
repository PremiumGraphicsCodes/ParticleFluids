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
	SceneFactory();

	~SceneFactory();

	void clear();

	ParticleSystemScene* addParticleSystemScene(const Math::Vector3dd& position, const ParticleAttribute& attribute, const std::string& name);

	ParticleSystemScene* addParticleSystemScene(const std::vector<Math::Vector3dd>& positions, const ParticleAttribute& attribute, const std::string& name);

	ParticleSystemScene* addParticleSystemScene(const std::vector<Math::Vector3dd>& positions, const std::vector<ParticleAttribute>& attributes, const std::string& name);

	WireFrameScene* addWireFrameScene(Shape::WireFrame* wire, const WireFrameAttribute& attribute, const std::string& name);

	PolygonMeshScene* addPolygonMeshScene(Shape::PolygonMesh* mesh, Graphics::Material* material, const std::string& name);

	void addLightScene(Graphics::PointLight* l, const std::string& name);

	MaterialScene* addMaterialScene(Graphics::Material* m, const std::string& name);

	std::vector<LightScene*> getLights() const { return lights; }

	int getNextId() { return idProvider.getNextId(); }

private:
	SceneIdProvider idProvider;
	std::vector<LightScene*> lights;
};

	}
}