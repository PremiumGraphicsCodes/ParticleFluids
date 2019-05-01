#include "ShaderObjectRepository.h"

using namespace Crystal::Shader;

ShaderObjectRepository::ShaderObjectRepository()
{
}

ShaderObjectRepository::~ShaderObjectRepository()
{
	clear();
}

void ShaderObjectRepository::clear()
{
	for (auto s : shaders) {
		s->clear();
		delete s;
	}
	shaders.clear();
}

int ShaderObjectRepository::add(const std::string& vsSource, const std::string& fsSource)
{
	ShaderObject* shader = new ShaderObject();
	shader->build(vsSource, fsSource);
	shaders.push_back(shader);
	return shader->getId();
}

ShaderObject* ShaderObjectRepository::findObjectById(const int id) const
{
	auto iter = std::find_if(std::cbegin(shaders), std::cend(shaders), [=](auto p) {return p->getId() == id; });
	if (iter == std::cend(shaders)) {
		return nullptr;
	}
	return *iter;
}