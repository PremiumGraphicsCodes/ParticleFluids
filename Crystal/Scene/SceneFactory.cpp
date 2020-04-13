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
