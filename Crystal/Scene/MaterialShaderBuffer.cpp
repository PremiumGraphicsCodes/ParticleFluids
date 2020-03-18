#include "MaterialShaderBuffer.h"

#include "../Graphics/Material.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

namespace {
	constexpr char* materialIdLabel = "materialId";
}

void MaterialShaderBuffer::add(const Material& m)
{
	this->materials.push_back(m);
}

void MaterialShaderBuffer::send(ShaderObject* shader)
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
