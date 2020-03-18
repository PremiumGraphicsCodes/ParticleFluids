#pragma once

#include "IRenderer.h"

namespace Crystal {
	namespace Shader {
		class ShaderObject;
	}
	namespace Scene {

class MaterialShaderScene
{
public:
	bool build(Shader::ShaderObject* shader);

	std::string getBuiltInFragmentShaderSource() const;
};

	}
}
