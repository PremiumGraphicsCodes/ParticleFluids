#pragma once

#include "ITextureObject.h"
#include "ShaderObject.h"
#include "IShader.h"
#include "GLObjectFactory.h"

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;

class OnScreenRenderer
{
public:
	bool build(GLObjectFactory& factory);

	void render(const ITextureObject& texture);

private:
	std::string getBuildinVertexShaderSource();

	std::string getBuildinFragmentShaderSource();

	void findLocation();

private:
	std::unique_ptr<ShaderObject> shader;
};

	}
}