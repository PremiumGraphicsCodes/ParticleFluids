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
	std::list<PointRenderer::GLBuffer> getPointBuffers() const { return pointBuffers; }

	std::list<LineBuffer> getLineBuffers() const { return lineBuffers; }

	std::list<SmoothTriangleBuffer> getTriangleBuffers() const { return triangleBuffers; }

	std::vector<Graphics::PointLight> getLights() const { return lights; }

	std::vector<Graphics::Material> getMaterials() const { return materials; }

	std::vector<Shader::TextureObject> getTextures() const { return textures; }

public:
	std::list<PointRenderer::GLBuffer> pointBuffers;
	std::list<LineBuffer> lineBuffers;
	std::list<SmoothTriangleBuffer> triangleBuffers;
	std::vector<Graphics::PointLight> lights;
	std::vector<Graphics::Material> materials;
	std::vector<Shader::TextureObject> textures;

};

	}
}