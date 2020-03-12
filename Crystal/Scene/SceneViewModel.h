#pragma once

#include "PointRenderer.h"
#include "LineRenderer.h"
#include "SmoothRenderer.h"
#include "../Graphics/PointLight.h"
#include "../Graphics/Material.h"
#include "../Shader/TextureObject.h"
#include <list>

namespace Crystal {
	namespace Scene {

class SceneViewModel
{
public:
	std::vector<Graphics::PointLight> getLights() const { return lights; }

	std::vector<Graphics::Material> getMaterials() const { return materials; }

public:
	std::vector<Graphics::PointLight> lights;
	std::vector<Graphics::Material> materials;
};

	}
}