#pragma once

#include "IRenderer.h"

#include "../Shape/PolygonMesh.h"
#include "../Graphics/Buffer1d.h"
#include "../Graphics/Buffer2d.h"
#include "../Graphics/Buffer3d.h"
#include "../Graphics/PointLight.h"
#include "../Graphics/Material.h"

namespace Crystal {
	namespace Scene {

class SmoothTriangleBuffer
{
public:
	SmoothTriangleBuffer() {}

	void addVertex(const Math::Vector3df& position, const Math::Vector3df& normal, const Math::Vector2df& texCoord, const int materialId)
	{
		positions.add(position);
		normals.add(normal);
		texCoords.add(texCoord);
		materialIds.add(materialId);
	}

	Graphics::Buffer3d<float> getPositions() const { return positions; }

	Graphics::Buffer3d<float> getNormals() const { return normals; }

	Graphics::Buffer2d<float> getTexCoords() const { return texCoords; }

	Graphics::Buffer1d<int> getMaterialIds() const { return materialIds; }

private:

	Graphics::Buffer3d<float> positions;
	Graphics::Buffer3d<float> normals;
	Graphics::Buffer2d<float> texCoords;
	Graphics::Buffer1d<int> materialIds;
};


class SmoothRenderer : public IRenderer
{
public:
	SmoothRenderer();

	void render(const Graphics::ICamera& camera) override;

	void setBuffer(const SmoothTriangleBuffer& buffer) {
		this->buffer = buffer;
	}

	void setLights(const std::vector<Graphics::PointLight>& lights) { this->lights = lights; }

	void setMaterials(const std::vector<Graphics::Material>& materials) { this->materials = materials; }

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	SmoothTriangleBuffer buffer;
	std::vector<Graphics::PointLight> lights;
	std::vector<Graphics::Material> materials;
};

	}
}