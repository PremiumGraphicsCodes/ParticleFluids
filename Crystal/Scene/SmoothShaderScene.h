#pragma once

#include "../Math/Matrix4d.h"
#include "../Graphics/Buffer1d.h"
#include "../Graphics/Buffer2d.h"
#include "../Graphics/Buffer3d.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Material.h"

#include "../Shader/VertexBufferObject.h"
#include "../Shader/SmoothRenderer.h"
#include "IShaderScene.h"

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class SmoothShader;
		class CameraShaderScene;

class SmoothBuffer
{
public:
	SmoothBuffer() :
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

class SmoothShaderScene : public IShaderScene
{
public:
	Shader::VertexBufferObject position;
	Shader::VertexBufferObject normal;
	Shader::VertexBufferObject texCoord;
	Shader::VertexBufferObject materialId;
	Shader::VertexBufferObject specularTexId;
	int count = 0;
	Math::Matrix4df matrix;

	explicit SmoothShaderScene(const std::string& name);

	bool build(Shader::GLObjectFactory& glFactory) override;

	void send(const SmoothBuffer& buffer);

	void release(Shader::GLObjectFactory& glFactory) override;

	void render() override;

	void setShader(Shader::SmoothRenderer* shader) { this->shader = shader; }

	void setCamera(CameraShaderScene* camera) { this->camera = camera; }

	CameraShaderScene* getCamera() const { return camera; }

private:
	Shader::SmoothRenderer* shader;
	CameraShaderScene* camera;
	Shader::SmoothRenderer::Buffer rBuffer;
};

	}
}