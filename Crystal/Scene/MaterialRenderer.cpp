#include "MaterialRenderer.h"

#include "../Graphics/Material.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

namespace {
	constexpr char* materialIdLabel = "materialId";
}

MaterialRenderer::MaterialRenderer()
{
}

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

void MaterialRenderer::add(const Material& m)
{
	this->materials.push_back(m);
}

void MaterialRenderer::send(ShaderObject* shader)
{
	shader->bind();
	for (int i = 0; i < materials.size(); ++i) {
		const auto m = materials[i];
		const auto prefix = "materials[" + std::to_string(i) + "]";
		shader->sendUniform(prefix + ".Ka", m.ambient);
		shader->sendUniform(prefix + ".Kd", m.diffuse);
		shader->sendUniform(prefix + ".Ks", m.specular);
		shader->sendUniform(prefix + ".shininess", m.shininess);
//		shader->sendUniform(prefix + ".ambientTexId", findIndex(m.ambientTexName));
//		shader->sendUniform(prefix + ".diffuseTexId", findIndex(m.diffuseTexName));// m.diffuseTexId);
//		shader->sendUniform(prefix + ".specularTexId", findIndex(m.specularTexName));// m.specularTexId);
	}

	shader->unbind();

	const auto error = glGetError();
	assert(error == GL_NO_ERROR);
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