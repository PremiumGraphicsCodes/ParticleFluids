#pragma once

#include "Crystal/Math/Vector3d.h"
#include "Crystal/Math/Matrix4d.h"
#include "Crystal/Graphics/Buffer1d.h"
#include "Crystal/Graphics/Buffer3d.h"
#include "Crystal/Graphics/Buffer4d.h"
#include "Crystal/Shader/VertexBufferObject.h"
#include "Crystal/Shader/GLObjectFactory.h"
#include "Crystal/Shader/ShaderBuildStatus.h"
#include <string>

namespace Crystal {
	namespace Photon {

struct PBVRBuffer
{
	Graphics::Buffer3d<float> positions;
	Graphics::Buffer1d<float> sizes;
	Graphics::Buffer1d<float> colors;
};

class PBVRenderer// : public IShaderScene
{
public:
	struct Buffer
	{

		Shader::VertexBufferObject position;
		Shader::VertexBufferObject size;
		Shader::VertexBufferObject color;
		Math::Matrix4dd projectionMatrix;
		Math::Matrix4dd modelViewMatrix;
		int count = 0;
	};

	PBVRenderer();

	Shader::ShaderBuildStatus build(Shader::GLObjectFactory& factory);

	void release(Shader::GLObjectFactory& factory);

	void render(const Buffer& buffer);

private:
	std::string getBuiltInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	Shader::ShaderObject* shader;
};

	}
}