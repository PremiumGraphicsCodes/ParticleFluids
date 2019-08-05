#include "SceneBuilder.h"

#include "../Graphics/PointLight.h"

#include "../Graphics/Image.h"
#include "../Shader/ShaderObject.h"
#include "ShaderScene.h"

#include "Scene.h"

#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

bool SceneBuilder::build()
{
	buildLight();

	scene.addScene(factory.createTextureScene(Image(512, 512), "OnScreenTexture"));

	Image image2(2, 2);
	image2.setColor(0, 0, ColorRGBAuc(255, 0, 0, 0));
	image2.setColor(1, 0, ColorRGBAuc(0, 255, 0, 0));
	image2.setColor(0, 1, ColorRGBAuc(0, 0, 255, 0));
	image2.setColor(1, 1, ColorRGBAuc(255, 255, 255, 0));
	scene.addScene(factory.createTextureScene(image2, "SmoothTexture"));

	scene.addScene(factory.createTextureScene(Image(512, 512), "IdTexture"));

	buildPointShader();
	buildLineShader();

	return true;
}

void SceneBuilder::buildLight()
{
	Graphics::PointLight light;
	light.setPosition(glm::vec3(100, 100, 100));
	light.setAmbient(glm::vec4(1, 1, 1, 1));
	light.setDiffuse(glm::vec4(1, 1, 1, 1));
	light.setSpecular(glm::vec4(1, 1, 1, 1));
	scene.addScene(factory.createLightScene(light, "Light"));

}

bool SceneBuilder::buildPointShader()
{

	/*
	auto sscene = factory.createShaderScene("PointShader");

	sscene->build();
	*/
	//scene.addScene(sscene);
	return true;
}

bool SceneBuilder::buildLineShader()
{
	/*
	std::string vsSource;
	{
		std::ostringstream stream;
		stream
			<< "#version 150" << std::endl
			<< "in vec3 position;" << std::endl
			<< "in vec4 color;" << std::endl
			<< "out vec4 vColor;" << std::endl
			<< "uniform mat4 projectionMatrix;" << std::endl
			<< "uniform mat4 modelviewMatrix;" << std::endl
			<< "void main(void)" << std::endl
			<< "{" << std::endl
			<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
			<< "	vColor = color;" << std::endl
			<< "}";
		vsSource = stream.str();
	}
	std::string fsSource;
	{
		std::ostringstream stream;
		stream
			<< "#version 150" << std::endl
			<< "in vec4 vColor;" << std::endl
			<< "out vec4 fragColor;" << std::endl
			<< "void main(void) {" << std::endl
			<< "	fragColor = vColor;" << std::endl
			<< "}" << std::endl;
		fsSource = stream.str();
	}
	auto shader = new ShaderObject();
	if (!shader->build(vsSource, fsSource)) {
		return false;
	}

	shader->findUniformLocation("projectionMatrix");
	shader->findUniformLocation("modelviewMatrix");

	shader->findAttribLocation("position");
	shader->findAttribLocation("color");
	scene.addScene(factory.createShaderScene(shader, "LineShader"));
	*/
	return true;
}
