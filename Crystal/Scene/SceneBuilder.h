#pragma once

#include "Scene.h"
#include "SceneFactory.h"

namespace Crystal {
	namespace Scene {

class SceneBuilder
{
public:
	SceneBuilder(Scene& scene, SceneFactory& factory) :
		scene(scene),
		factory(factory)
	{}

	bool build();

private:
	bool buildPointShader();

	bool buildLineShader();

	bool buildSmoothShader();

private:
	Scene& scene;
	SceneFactory& factory;
};
	}
}