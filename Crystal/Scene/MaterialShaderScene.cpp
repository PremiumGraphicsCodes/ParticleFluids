#include "MaterialShaderScene.h"

#include <sstream>

using namespace Crystal::Shader;
using namespace Crystal::Scene;

bool MaterialShaderScene::build(ShaderObject* shader)
{
	for (int i = 0; i < 256; ++i) {
		const auto prefix = "materials[" + std::to_string(i) + "]";
		shader->findUniformLocation(prefix + ".Ka");
		shader->findUniformLocation(prefix + ".Kd");
		shader->findUniformLocation(prefix + ".Ks");
		shader->findUniformLocation(prefix + ".shininess");
		shader->findUniformLocation(prefix + ".ambientTexId");
		shader->findUniformLocation(prefix + ".diffuseTexId");
		shader->findUniformLocation(prefix + ".specularTexId");
	}
	return true;
}

std::string MaterialShaderScene::getBuiltInFragmentShaderSource() const
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