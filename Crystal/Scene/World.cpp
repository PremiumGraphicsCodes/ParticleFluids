#include "World.h"

#include "PointShader.h"
#include "LightScene.h"
#include "MaterialScene.h"
#include "TextureScene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

World::World()
{
	scenes[0] = std::make_unique<Scene>(0, "Item");
	scenes[1] = std::make_unique<Scene>(0, "Root");

}

World::~World()
{
	clear();
}

void World::init()
{
	renderer = std::make_unique<SceneShader>();

	{
		auto light = std::make_unique<PointLight>();
		light->setPosition(Vector3dd(100, 100, 100));
		light->setAmbient(ColorRGBAf(1, 1, 1, 1));
		light->setDiffuse(ColorRGBAf(1, 1, 1, 1));
		light->setSpecular(ColorRGBAf(1, 1, 1, 1));
		scenes[1]->addScene(sceneFactory.createLightScene(std::move(light), "Light0"));
	}

	{
		auto material = std::make_unique<Material>();
		material->ambient = ColorRGBAf(1, 1, 1, 1);
		material->diffuse = ColorRGBAf(1, 1, 1, 1);
		material->specular = ColorRGBAf(1, 1, 1, 1);
		material->shininess = 1.0;
		material->ambientTexName = "WhiteTex";
		scenes[1]->addScene(sceneFactory.createMaterialScene(std::move(material), "WhiteMat"));
	}

	{
		auto material = std::make_unique<Material>();
		material->ambient = ColorRGBAf(1, 0, 0, 1);
		material->diffuse = ColorRGBAf(0, 0, 0, 1);
		material->specular = ColorRGBAf(0, 0, 0, 1);
		material->shininess = 1.0;
		scenes[1]->addScene(sceneFactory.createMaterialScene(std::move(material), "RedMat"));
	}


	{
		auto material = std::make_unique<Material>();
		material->ambient = ColorRGBAf(0, 0, 0, 1);
		material->diffuse = ColorRGBAf(0, 0, 0, 1);
		material->specular = ColorRGBAf(0, 0, 0, 1);
		material->shininess = 1.0;
		scenes[1]->addScene(sceneFactory.createMaterialScene(std::move(material), "BlackMat"));
	}

	{
		auto image = std::make_unique<Image>(2,2);
		image->setColor(0, 0, ColorRGBAuc(255, 0, 0, 255));
		image->setColor(0, 1, ColorRGBAuc(0, 255, 0, 255));
		image->setColor(1, 0, ColorRGBAuc(0, 255, 255, 255));
		image->setColor(1, 1, ColorRGBAuc(0, 0, 0, 255));

//		auto tex = glFactory.getTextureFactory()->createTextureObject(image);
		auto s = sceneFactory.createTextureScene(std::move(image), "WhiteTex");
//		s->build();
		scenes[1]->addScene(s);
	}

	{
		auto image = std::make_unique<Image>(1, 1);
		image->setColor(0, 0, ColorRGBAuc(0, 0, 0, 0));
		auto s = sceneFactory.createTextureScene(std::move(image), "BlackTex");
//		s->build();
		scenes[1]->addScene(s);
	}


	renderer = std::make_unique<SceneShader>();

}

void World::clear()
{
	glFactory.clear();
	sceneFactory.clear();
	for (auto& s : scenes) {
		s->clear();
	}
}

void World::clear(int layer)
{
	scenes[layer]->clear();
}

void World::addScene(int layer, IScene* scene)
{
	scenes[layer]->addScene(scene);
}

Box3d World::getBoundingBox() const
{
	return scenes[1]->getBoundingBox();
}
