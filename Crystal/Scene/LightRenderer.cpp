#include "LightRenderer.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

LightRenderer::LightRenderer()
{
}

bool LightRenderer::build(IRenderer* parent)
{
	for (int i = 0; i < 8; ++i) {
		const auto prefix = "lights[" + std::to_string(i) + "]";
		parent->addUniform(prefix + ".position");
		parent->addUniform(prefix + ".La");
		parent->addUniform(prefix + ".Ld");
		parent->addUniform(prefix + ".Ls");
	}
	return true;
}

void LightRenderer::setLights(const std::vector<PointLight>& lights, ShaderObject* shader)
{
	shader->bind();
	for (int i = 0; i < lights.size(); ++i) {
		const auto light = lights[i];
		const auto& lightPos = light.getPosition();//{ -10.0f, 10.0f, 10.0f };
		const auto& ambient = light.getAmbient();
		const auto& diffuse = light.getDiffuse();
		const auto& specular = light.getSpecular();

		const auto prefix = "lights[" + std::to_string(i) + "]";

		shader->sendUniform(prefix + ".position", lightPos);
		shader->sendUniform(prefix + ".La", ambient);
		shader->sendUniform(prefix + ".Ld", diffuse);
		shader->sendUniform(prefix + ".Ls", specular);
	}
	shader->unbind();
}
