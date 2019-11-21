#include "SceneFactory.h"

#include "Scene.h"

#include "IRenderer.h"
#include "LightScene.h"
#include "ParticleSystemScene.h"
#include "WireFrameScene.h"
#include "PolygonMeshScene.h"
#include "TransformScene.h"
#include "FaceGroupScene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

SceneFactory::SceneFactory()
{
}

SceneFactory::~SceneFactory()
{
	clear();
}

void SceneFactory::clear()
{
	idProvider.reset();
}

Scene* SceneFactory::createScene(const std::string& name)
{
	return new Scene(getNextId(), name);
}

ParticleSystemScene* SceneFactory::createParticleSystemScene(const Vector3dd& position, const ParticleAttribute& attribute, const std::string& name)
{
	auto particles = new ParticleSystem<ParticleAttribute>();
	particles->add(position, attribute);
	return new ParticleSystemScene(getNextId(), name, particles);
}

ParticleSystemScene* SceneFactory::createParticleSystemScene(const std::vector<Vector3dd>& positions, const ParticleAttribute& attribute, const std::string& name)
{
	auto particles = new ParticleSystem<ParticleAttribute>();
	for (const auto& p : positions) {
		particles->add(p, attribute);
	}
	return new ParticleSystemScene(getNextId(), name, particles);
}

ParticleSystemScene* SceneFactory::createParticleSystemScene(const std::vector<Vector3dd>& positions, const std::vector<ParticleAttribute>& attributes, const std::string& name)
{
	assert(positions.size() == attributes.size());
	auto particles = new ParticleSystem<ParticleAttribute>();
	for (int i = 0; i < positions.size(); ++i) {
		particles->add(positions[i], attributes[i]);
	}
	return new ParticleSystemScene(getNextId(), name, particles);
}

WireFrameScene* SceneFactory::createWireFrameScene(const std::vector<Vector3dd>& positions, const std::vector<WireFrameEdge>& edges, const WireFrameAttribute& attribute, const std::string& name)
{
	return new WireFrameScene(getNextId(), name, positions, edges, attribute);
}

PolygonMeshScene* SceneFactory::createPolygonMeshScene(PolygonMesh* mesh,  const std::string& name)
{
	return new PolygonMeshScene(getNextId(), name, mesh);
}

LightScene* SceneFactory::createLightScene(const PointLight& light, const std::string& name)
{
	return new LightScene(getNextId(), name, light);
}

MaterialScene* SceneFactory::createMaterialScene(const Material& material, const std::string& name)
{
	return new MaterialScene(getNextId(), name, material);
}

TextureScene* SceneFactory::createTextureScene(const Image& image, const std::string& name)
{
	return new TextureScene(getNextId(), name, image);
}

/*
ShaderScene* SceneFactory::createShaderScene(const std::string& name)
{
	return new ShaderScene(getNextId(), name);
}

CameraScene* SceneFactory::createCameraScene(ICamera* camera, const std::string& name)
{
	return new CameraScene(getNextId(), name, camera);
}
*/

TransformScene* SceneFactory::createTransformScene(const std::string& name)
{
	return new TransformScene(getNextId(), name);
}

FaceGroupScene* SceneFactory::createFaceGroupScene(PolygonMeshScene* parent, const std::string& name)
{
	auto g= new FaceGroupScene(getNextId(), name);
	parent->addGroup(g);
	return g;
}
