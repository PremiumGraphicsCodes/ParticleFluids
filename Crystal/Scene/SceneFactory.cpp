#include "SceneFactory.h"

#include "Scene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

SceneFactory::SceneFactory() :
	idProvider(1)
{
}

SceneFactory::~SceneFactory()
{
	clear();
}

void SceneFactory::clear()
{
	idProvider.reset(1);
}
