#pragma once

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

	std::string getBuiltInFragmentShaderSource() const;
};

	}
}
