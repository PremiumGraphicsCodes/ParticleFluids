#pragma once

#include "ShaderObject.h"
#include <memory>

namespace Crystal {
	namespace Shader {
		class ITextureObject;
		class GLObjectFactory;

class BillBoardRenderer
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