#pragma once

#include "MaterialShaderBuffer.h"

#include <string>

namespace Crystal {
	namespace Shader {
		class ShaderObject;
	}
	namespace Scene {

class MaterialShaderScene
{
public:
	bool build(Shader::ShaderObject* shader);

	void send(Shader::ShaderObject* shader, const MaterialShaderBuffer& buffer);

	std::string getBuiltInFragmentShaderSource() const;
};

	}
}
