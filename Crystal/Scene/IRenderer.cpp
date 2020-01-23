#include "IRenderer.h"

#include "../Shader/GLObjectFactory.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

bool IRenderer::build(GLObjectFactory& factory)
{
	this->shader = factory.getShaderFactory()->create(vsSource, fsSource); //std::make_unique<ShaderObject>();
	if (!shader->isBuildOK()) {
		return false;
	}
	for (const auto& u : uniforms) {
		shader->findUniformLocation(u);
	}
	for (const auto& a : attributes) {
		shader->findAttribLocation(a);
	}
	return true;
}