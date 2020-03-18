#pragma once

#include "../Graphics/Buffer1d.h"
#include "../Graphics/Buffer2d.h"
#include "../Graphics/Buffer3d.h"
#include "../Graphics/PointLight.h"
#include "../Graphics/Material.h"
#include "../Graphics/Camera.h"

#include "../Math/Matrix4d.h"

#include "../Shader/TextureObject.h"
#include "../Shader/VertexBufferObject.h"

#include "MaterialBuffer.h"
#include "MaterialShaderScene.h"
#include "LightShaderScene.h"
#include "TextureShaderScene.h"

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


class SmoothShaderScene
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

		void send(const SmoothTriangleBuffer& buffer);

		void release();

		MaterialBuffer materialBuffer;
	};

	SmoothShaderScene();

	bool build();

	void send(const GLBuffer& buffer, const Graphics::Camera& camera);

	void render(const Graphics::Camera& camera);

	LightShaderScene* getLightRenderer() { return &lightShader; }

	TextureShaderScene* getTextureRenderer() { return &textureShader; }

	Shader::ShaderObject* getShader() { return &shader; }

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	MaterialShaderScene materialShader;
	LightShaderScene lightShader;
	TextureShaderScene textureShader;
	Math::Matrix4df matrix;
	int count;
	Shader::ShaderObject shader;
};

	}
}