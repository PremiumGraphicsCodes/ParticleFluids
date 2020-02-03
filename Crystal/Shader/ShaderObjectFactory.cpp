#include "ShaderObjectFactory.h"

using namespace Crystal::Shader;

void ShaderObjectFactory::clear()
{
}

std::unique_ptr<ShaderObject> ShaderObjectFactory::create(const std::string& vsSource, const std::string& fsSource)
{
	auto shader = std::make_unique<ShaderObject>();
	shader->build(vsSource, fsSource);
	return std::move(shader);
}
