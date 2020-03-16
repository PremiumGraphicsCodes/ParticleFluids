#include "MaterialRenderer.h"

#include "../Graphics/Material.h"

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

/*
void MaterialRenderer::send()
{
	auto shader = getShader();
	shader->bind();

	for (int i = 0; i < materials.size(); ++i) {
		const auto m = materials[i];
		const auto prefix = "materials[" + std::to_string(i) + "]";
		shader->sendUniform(prefix + ".Ka", m.ambient);
		shader->sendUniform(prefix + ".Kd", m.diffuse);
		shader->sendUniform(prefix + ".Ks", m.specular);
		shader->sendUniform(prefix + ".shininess", m.shininess);
		shader->sendUniform(prefix + ".ambientTexId", findIndex(m.ambientTexName));
		shader->sendUniform(prefix + ".diffuseTexId", findIndex(m.diffuseTexName));// m.diffuseTexId);
		shader->sendUniform(prefix + ".specularTexId", findIndex(m.specularTexName));// m.specularTexId);
	}

	shader->unbind();

	const auto error = glGetError();
	assert(error == GL_NO_ERROR);
}

void MaterialRenderer::render(const Camera& camera)
{
	auto shader = getShader();

	shader->sendVertexAttribute1di(::materialIdLabel, glBuffer.vbo.materialId);


	shader->enableVertexAttribute(::positionLabel);
	shader->enableVertexAttribute(::normalLabel);
	shader->enableVertexAttribute(::texCoordLabel);
	shader->enableVertexAttribute(::materialIdLabel);

	//textures[0].unbind();

	shader->disableVertexAttribute(::materialIdLabel);
	shader->disableVertexAttribute(::texCoordLabel);
	shader->disableVertexAttribute(::normalLabel);
	shader->disableVertexAttribute(::positionLabel);

	assert(GL_NO_ERROR == glGetError());

	shader->disableDepthTest();
	shader->unbind();
}
*/