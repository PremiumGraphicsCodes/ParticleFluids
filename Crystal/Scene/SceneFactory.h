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

	ParticleSystemScene* createParticleSystemScene(const Math::Vector3dd& position, const ParticleAttribute& attribute, const std::string& name);

	ParticleSystemScene* createParticleSystemScene(const std::vector<Math::Vector3dd>& positions, const ParticleAttribute& attribute, const std::string& name);

	ParticleSystemScene* createParticleSystemScene(const std::vector<Math::Vector3dd>& positions, const std::vector<ParticleAttribute>& attributes, const std::string& name);

	WireFrameScene* createWireFrameScene(Shape::WireFrame* wire, const WireFrameAttribute& attribute, const std::string& name);

	PolygonMeshScene* createPolygonMeshScene(Shape::PolygonMesh* mesh, MaterialScene* material, const std::string& name);

	LightScene* createLightScene(Graphics::PointLight* l, const std::string& name);

	MaterialScene* createMaterialScene(const std::string& name);

	int getNextId() { return idProvider.getNextId(); }

private:
	SceneIdProvider idProvider;
};

	}
}