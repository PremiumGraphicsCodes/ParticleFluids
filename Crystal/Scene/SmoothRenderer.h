#pragma once

#include "IRenderer.h"

#include "../Graphics/Buffer1d.h"
#include "../Graphics/Buffer2d.h"
#include "../Graphics/Buffer3d.h"
#include "../Graphics/PointLight.h"
#include "../Graphics/Material.h"

#include "../Math/Matrix4d.h"

#include "../Shader/TextureObject.h"
#include "../Shader/VertexBufferObject.h"

namespace Crystal {
	namespace Scene {

class SmoothTriangleBuffer
{
public:
	SmoothTriangleBuffer() :
		matrix(Math::Identity())
	{}

	void addVertex(const Math::Vector3df& position, const Math::Vector3df& normal, const Math::Vector2df& texCoord, const int materialId);

	Graphics::Buffer3d<float> getPositions() const { return positions; }

	Graphics::Buffer3d<float> getNormals() const { return normals; }

	Graphics::Buffer2d<float> getTexCoords() const { return texCoords; }

	Graphics::Buffer1d<int> getMaterialIds() const { return materialIds; }

	void setMatrix(const Math::Matrix4dd& matrix) { this->matrix = matrix; }

	Math::Matrix4dd getMatrix() const { return matrix; }

private:
	Math::Matrix4dd matrix;
	Graphics::Buffer3d<float> positions;
	Graphics::Buffer3d<float> normals;
	Graphics::Buffer2d<float> texCoords;
	Graphics::Buffer1d<int> materialIds;
};


class SmoothRenderer : public IRenderer
{
public:
	struct GLBuffer {
		Shader::VertexBufferObject position;
		Shader::VertexBufferObject normal;
		Shader::VertexBufferObject texCoord;
		Shader::VertexBufferObject materialId;
		Shader::VertexBufferObject specularTexId;
		int count = 0;
		Math::Matrix4df matrix;

		void build();

		void release();

		void send(const SmoothTriangleBuffer& buffer);
	};

	SmoothRenderer();

	bool build(Shader::GLObjectFactory& factory) override;

	void setBuffer(const GLBuffer& buffer) { glBuffer = buffer; }

	void render(const Graphics::Camera& camera) override;

	void setLights(const std::vector<Graphics::PointLight>& lights);

	void setMaterials(const std::vector<Graphics::Material>& materials) { this->materials = materials; }

	void setTextures(const std::vector<Shader::TextureObject>& textures);

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	std::vector<Graphics::PointLight> lights;
	std::vector<Graphics::Material> materials;

	GLBuffer glBuffer;
};

	}
}