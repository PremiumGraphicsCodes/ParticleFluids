#include "MaterialRenderer.h"

#include <sstream>

using namespace Crystal::Scene;

bool MaterialRenderer::build(IRenderer* parent)
{
	for (int i = 0; i < 256; ++i) {
		const auto prefix = "materials[" + std::to_string(i) + "]";
		parent->addUniform(prefix + ".Ka");
		parent->addUniform(prefix + ".Kd");
		parent->addUniform(prefix + ".Ks");
		parent->addUniform(prefix + ".shininess");
		parent->addUniform(prefix + ".ambientTexId");
		parent->addUniform(prefix + ".diffuseTexId");
		parent->addUniform(prefix + ".specularTexId");
	}
	return true;
}


std::string MaterialRenderer::getBuiltInFragmentShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "struct MaterialInfo {" << std::endl
		<< "	vec3 Ka;" << std::endl
		<< "	vec3 Kd;" << std::endl
		<< "	vec3 Ks;" << std::endl
		<< "	float shininess;" << std::endl
		<< "	int ambientTexId;" << std::endl
		<< "	int diffuseTexId;" << std::endl
		<< "	int specularTexId;" << std::endl
		<< "};"
		<< "uniform MaterialInfo materials[256];" << std::endl;
	return stream.str();
}