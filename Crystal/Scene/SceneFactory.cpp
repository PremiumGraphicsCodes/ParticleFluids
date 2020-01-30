#include "SceneFactory.h"

#include "Scene.h"

#include "IRenderer.h"
#include "LightScene.h"
#include "ParticleSystemScene.h"
#include "WireFrameScene.h"
#include "PolygonMeshScene.h"
#include "TransformScene.h"
#include "FaceGroupScene.h"
#include "TextureScene.h"

#include "../Shape/WireFrame.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

SceneFactory::SceneFactory() :
	idProvider(1),
	materialIdProvider(0)
{
}

SceneFactory::~SceneFactory()
{
	clear();
}

void SceneFactory::clear()
{
	idProvider.reset(1);
	materialIdProvider.reset(0);
}

Scene* SceneFactory::createScene(const std::string& name)
{
	return new Scene(getNextId(), name);
}

ParticleSystemScene* SceneFactory::createParticleSystemScene(const Vector3dd& position, const ParticleAttribute& attribute, const std::string& name)
{
	auto particles = std::make_unique<ParticleSystem<ParticleAttribute>>();
	particles->add(position, attribute);
	return new ParticleSystemScene(getNextId(), name, std::move(particles));
}

ParticleSystemScene* SceneFactory::createParticleSystemScene(const std::vector<Vector3dd>& positions, const ParticleAttribute& attribute, const std::string& name)
{
	auto particles = std::make_unique<ParticleSystem<ParticleAttribute>>();
	for (const auto& p : positions) {
		particles->add(p, attribute);
	}
	return new ParticleSystemScene(getNextId(), name, std::move(particles));
}

ParticleSystemScene* SceneFactory::createParticleSystemScene(const std::vector<Vector3dd>& positions, const std::vector<ParticleAttribute>& attributes, const std::string& name)
{
	assert(positions.size() == attributes.size());
	auto particles = std::make_unique<ParticleSystem<ParticleAttribute>>();
	for (int i = 0; i < positions.size(); ++i) {
		particles->add(positions[i], attributes[i]);
	}
	return new ParticleSystemScene(getNextId(), name, std::move(particles));
}

WireFrameScene* SceneFactory::createWireFrameScene(std::unique_ptr<WireFrame> shape, const WireFrameAttribute& attribute, const std::string& name)
{
	return new WireFrameScene(getNextId(), name, std::move(shape), attribute);
}

PolygonMeshScene* SceneFactory::createPolygonMeshScene(std::unique_ptr<PolygonMesh> mesh,  const std::string& name)
{
	return new PolygonMeshScene(getNextId(), name, std::move(mesh));
}

LightScene* SceneFactory::createLightScene(std::unique_ptr<PointLight> light, const std::string& name)
{
	return new LightScene(getNextId(), name, std::move(light));
}

MaterialScene* SceneFactory::createMaterialScene(std::unique_ptr<Material> material, const std::string& name)
{
	return new MaterialScene(getNextId(), name, std::move(material), materialIdProvider.getNextId());
}

TextureScene* SceneFactory::createTextureScene(const Image& image, const std::string& name)
{
	return new TextureScene(getNextId(), image, name);
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
	auto g= new FaceGroupScene(getNextId(), name, parent);
	parent->addGroup(g);
	return g;
}
