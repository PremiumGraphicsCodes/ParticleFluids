#include "LightShaderScene.h"

#include "../Shader/ShaderObject.h"

#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

bool LightShaderBuffer::build()
{
	return true;
}

void LightShaderBuffer::send()
{

}


void LightShaderBuffer::add(const PointLight& light)
{
	lights.push_back(light);
}

LightShaderScene::LightShaderScene()
{
}

void LightShaderScene::setShader(ShaderObject* shader)
{
	this->shader = shader;
}

bool LightShaderScene::build()
{
	for (int i = 0; i < 8; ++i) {
		const auto prefix = "lights[" + std::to_string(i) + "]";
		shader->findUniformLocation(prefix + ".position");
		shader->findUniformLocation(prefix + ".La");
		shader->findUniformLocation(prefix + ".Ld");
		shader->findUniformLocation(prefix + ".Ls");
	}
	return true;
}


void LightShaderScene::send()
{
	const auto& lights = buffer.getLights();

	shader->bind();
	for (int i = 0; i < lights.size(); ++i) {
		const auto& light = lights[i];
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

std::string LightShaderScene::getBuiltInFragmentShaderSource() const
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