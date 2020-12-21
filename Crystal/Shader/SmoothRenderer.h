#pragma once

#include "GLObjectFactory.h"
#include "VertexBufferObject.h"
#include "../Math/Matrix4d.h"
#include "../Math/Vector3d.h"
#include "../Graphics/Material.h"
#include "../Shader/TextureObject.h"
#include "../Shader/ShaderObject.h"

namespace Crystal {
	namespace Shader {

class SmoothRenderer
{
public:
	struct Buffer
	{
		VertexBufferObject position;
		VertexBufferObject normal;
		VertexBufferObject texCoord;
		VertexBufferObject materialId;
		VertexBufferObject specularTexId;

		std::vector<Shader::TextureObject> textures;


		Math::Matrix4df matrix;
		Math::Matrix4df projectionMatrix;
		Math::Matrix4df modelViewMatrix;
		Math::Vector3df eyePosition;

		int count;
	};

	SmoothRenderer();

	bool build(Shader::GLObjectFactory& factory);

	void release(Shader::GLObjectFactory& factory);

	void setMaterial(const int index, const Graphics::Material& material);

	/*
	void send(const std::vector<PointLight>& lights);
	*/

	//void send(const std::vector<Shader::TextureObject>& textures);

	void render(const Buffer& buffer);

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	Shader::ShaderObject* shader;
};

	}
}