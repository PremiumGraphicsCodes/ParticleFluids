#pragma once

#include "ShaderObject.h"
#include "ShaderBuildStatus.h"
#include <memory>

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
		class ITextureObject;

class OnScreenRenderer
{
public:
	ShaderBuildStatus build(GLObjectFactory& factory);

	void release(GLObjectFactory& factory);

	void render(const ITextureObject& texture);

private:
	std::string getBuildinVertexShaderSource();

	std::string getBuildinFragmentShaderSource();

	void findLocation();

private:
	ShaderObject* shader;
};

	}
}