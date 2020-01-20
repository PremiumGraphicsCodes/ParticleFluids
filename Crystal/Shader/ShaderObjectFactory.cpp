#include "ShaderObjectFactory.h"

using namespace Crystal::Shader;

void ShaderObjectFactory::clear()
{
	for (const auto& s : shaders) {
		s->clear();
	}
	shaders.clear();
}

ShaderObject* ShaderObjectFactory::create(const std::string& vsSource, const std::string& fsSource)
{
	shaders.push_back(std::make_unique<ShaderObject>());
	shaders.back()->build(vsSource, fsSource);
	return shaders.back().get();
}
