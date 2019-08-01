#pragma once

#include "Scene.h"
#include "SceneFactory.h"

namespace Crystal {
	namespace Scene {

class SceneBuilder
{
public:
	static void build(Scene& scene, SceneFactory& factory);
};
	}
}