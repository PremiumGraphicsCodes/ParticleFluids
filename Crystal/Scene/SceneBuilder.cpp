#include "SceneBuilder.h"

#include "../Graphics/PointLight.h"

#include "../Graphics/Image.h"

#include "Scene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

bool SceneBuilder::build()
{
	Graphics::PointLight light;
	light.setPosition(glm::vec3(100, 100, 100));
	light.setAmbient(glm::vec4(1, 1, 1, 1));
	light.setDiffuse(glm::vec4(1, 1, 1, 1));
	light.setSpecular(glm::vec4(1, 1, 1, 1));
	scene.addScene(factory.createLightScene(light, "Light"));

	scene.addScene(factory.createTextureScene(Image(512, 512), "OnScreenTexture"));

	Image image2(2, 2);
	image2.setColor(0, 0, ColorRGBAuc(255, 0, 0, 0));
	image2.setColor(1, 0, ColorRGBAuc(0, 255, 0, 0));
	image2.setColor(0, 1, ColorRGBAuc(0, 0, 255, 0));
	image2.setColor(1, 1, ColorRGBAuc(255, 255, 255, 0));
	scene.addScene(factory.createTextureScene(image2, "SmoothTexture"));

	scene.addScene(factory.createTextureScene(Image(512, 512), "IdTexture"));

	return true;
}
