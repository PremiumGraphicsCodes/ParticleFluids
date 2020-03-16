#include "LightRenderer.h"

#include <sstream>

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

void LightRenderer::GLBuffer::add(const PointLight& light)
{
	lights.push_back(light);
}

void LightRenderer::send(ShaderObject* shader)
{
	shader->bind();
	for (int i = 0; i < glBuffer.lights.size(); ++i) {
		const auto& light = glBuffer.lights[i];
		const auto prefix = "lights[" + std::to_string(i) + "]";

		const auto& lightPos = light.getPosition();//{ -10.0f, 10.0f, 10.0f };
		const auto& ambient = light.getAmbient();
		const auto& diffuse = light.getDiffuse();
		const auto& specular = light.getSpecular();

		shader->sendUniform(prefix + ".position", lightPos);
		shader->sendUniform(prefix + ".La", ambient);
		shader->sendUniform(prefix + ".Ld", diffuse);
		shader->sendUniform(prefix + ".Ls", specular);
	}
	shader->unbind();
}

std::string LightRenderer::getBuiltInFragmentShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "struct LightInfo {" << std::endl
		<< "	vec3 position;" << std::endl
		<< "	vec3 La;" << std::endl
		<< "	vec3 Ld;" << std::endl
		<< "	vec3 Ls;" << std::endl
		<< "};"
		<< "uniform LightInfo lights[8];";
	return stream.str();
}