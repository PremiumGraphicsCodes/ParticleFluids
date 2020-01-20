#pragma once

#include "IRenderer.h"

#include "../Graphics/Buffer1d.h"
#include "../Graphics/Buffer2d.h"
#include "../Graphics/Buffer3d.h"
#include "../Graphics/PointLight.h"
#include "../Graphics/Material.h"

#include "../Math/Matrix4d.h"

#include "../Shader/TextureObject.h"

namespace Crystal {
	namespace Scene {

class SmoothTriangleBuffer
{
public:
	SmoothTriangleBuffer() :
		matrix(Math::Identity())
	{}

	void addVertex(const Math::Vector3df& position, const Math::Vector3df& normal, const Math::Vector2df& texCoord, const int materialId, const int ambientTexId, const int diffuseTexId, const int specularId);

	Graphics::Buffer3d<float> getPositions() const { return positions; }

	Graphics::Buffer3d<float> getNormals() const { return normals; }

	Graphics::Buffer2d<float> getTexCoords() const { return texCoords; }

	Graphics::Buffer1d<int> getMaterialIds() const { return materialIds; }

	Graphics::Buffer1d<int> getAmbientTexIds() const { return ambientTexIds; }

	Graphics::Buffer1d<int> getDiffuseTexIds() const { return diffuseTexIds; }

	Graphics::Buffer1d<int> getSpecularTexIds() const { return specularTexIds; }

	void setMatrix(const Math::Matrix4dd& matrix) { this->matrix = matrix; }

	Math::Matrix4dd getMatrix() const { return matrix; }

private:
	Math::Matrix4dd matrix;
	Graphics::Buffer3d<float> positions;
	Graphics::Buffer3d<float> normals;
	Graphics::Buffer2d<float> texCoords;
	Graphics::Buffer1d<int> materialIds;
	Graphics::Buffer1d<int> ambientTexIds;
	Graphics::Buffer1d<int> diffuseTexIds;
	Graphics::Buffer1d<int> specularTexIds;
};


class SmoothRenderer : public IRenderer
{
public:
	SmoothRenderer();

	void render(const Graphics::Camera& camera) override;

	void setBuffer(const SmoothTriangleBuffer& buffer, const std::vector<Shader::TextureObject>& textures) {
		this->buffer = buffer;
		this->textures = textures;
	}

	void setLights(const std::vector<Graphics::PointLight>& lights) { this->lights = lights; }

	void setMaterials(const std::vector<Graphics::Material>& materials) { this->materials = materials; }

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	SmoothTriangleBuffer buffer;
	std::vector<Graphics::PointLight> lights;
	std::vector<Graphics::Material> materials;
	std::vector<Shader::TextureObject> textures;
};

	}
}