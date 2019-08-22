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

class SmoothFaceGroupBuffer
{
public:
	explicit SmoothFaceGroupBuffer(const int materialId) :
		materialId(materialId)
	{
	}

	void addFace(const int i0, const int i1, const int i2)
	{
		indices.add(i0);
		indices.add(i1);
		indices.add(i2);
	}

	Graphics::Buffer1d<unsigned int> indices;
	int materialId;
};

class SmoothTriangleBuffer
{
public:
	SmoothTriangleBuffer() {}

	void addVertex(const Math::Vector3df& position, const Math::Vector3df& normal, const Math::Vector2df& texCoord)
	{
		positions.add(position);
		normals.add(normal);
		texCoords.add(texCoord);
	}

	void addGroup(const SmoothFaceGroupBuffer& group)
	{
		groups.push_back(group);
	}

	Graphics::Buffer3d<float> getPositions() const { return positions; }

	Graphics::Buffer3d<float> getNormals() const { return normals; }

	Graphics::Buffer2d<float> getTexCoords() const { return texCoords; }

	std::vector<SmoothFaceGroupBuffer> getGroups() const { return groups; }

private:
	Graphics::Buffer3d<float> positions;
	Graphics::Buffer3d<float> normals;
	Graphics::Buffer2d<float> texCoords;
	std::vector<SmoothFaceGroupBuffer> groups;
};


class SmoothRenderer : public IRenderer
{
public:
	SmoothRenderer(const int id, const std::string& name);

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