#include "SceneBuilder.h"

#include "../Graphics/PointLight.h"

#include "../Graphics/Image.h"

#include "Scene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

void SceneBuilder::build(Scene& objects, SceneFactory& objectFactory)
{
	Graphics::PointLight light;
	light.setPosition(glm::vec3(100, 100, 100));
	light.setAmbient(glm::vec4(1, 1, 1, 1));
	light.setDiffuse(glm::vec4(1, 1, 1, 1));
	light.setSpecular(glm::vec4(1, 1, 1, 1));
	objects.addScene(objectFactory.createLightScene(light, "Light"));

	objects.addScene(objectFactory.createTextureScene(Image(512, 512), "OnScreenTexture"));

	Image image2(2, 2);
	image2.setColor(0, 0, ColorRGBAuc(255, 0, 0, 0));
	image2.setColor(1, 0, ColorRGBAuc(0, 255, 0, 0));
	image2.setColor(0, 1, ColorRGBAuc(0, 0, 255, 0));
	image2.setColor(1, 1, ColorRGBAuc(255, 255, 255, 0));
	objects.addScene(objectFactory.createTextureScene(image2, "SmoothTexture"));

	objects.addScene(objectFactory.createTextureScene(Image(512, 512), "IdTexture"));

}
