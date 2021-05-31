#pragma once

#include "GLObjectFactory.h"
#include "VertexBufferObject.h"
#include "../Math/Matrix4d.h"
#include "../Math/Vector3d.h"
#include "../Graphics/Material.h"
#include "../Graphics/PointLight.h"
#include "../Shader/TextureObject.h"
#include "../Shader/ShaderObject.h"
#include "../Shader/ShaderBuildStatus.h"

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

		Math::Matrix4df matrix;
		Math::Matrix4df projectionMatrix;
		Math::Matrix4df modelViewMatrix;
		Math::Vector3df eyePosition;
	};

	struct BufferBlock
	{
		std::vector<unsigned int> vertexIndices;
		Graphics::Material material;
		Shader::TextureObject texture;
	};

	SmoothRenderer();

	ShaderBuildStatus build(Shader::GLObjectFactory& factory);

	void release(Shader::GLObjectFactory& factory);

	void sendLight(const int index, const Graphics::PointLight& light);

	void render(const Buffer& buffer, const std::vector<BufferBlock>& blocks);

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	Shader::ShaderObject* shader;
};

	}
}