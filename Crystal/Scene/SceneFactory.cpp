#include "SceneFactory.h"

#include "Scene.h"

#include "LightScene.h"
#include "ParticleSystemScene.h"
#include "WireFrameScene.h"
#include "TriangleMeshScene.h"
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

ParticleSystemScene* SceneFactory::createParticleSystemScene(const std::vector<Vector3dd>& positions, const std::vector<ParticleAttribute>& attributes, const std::string& name)
{
	assert(positions.size() == attributes.size());
	auto particles = std::make_unique<ParticleSystem<ParticleAttribute>>();
	for (int i = 0; i < positions.size(); ++i) {
		particles->add(positions[i], attributes[i]);
	}
	return new ParticleSystemScene(getNextId(), name, std::move(particles));
}
