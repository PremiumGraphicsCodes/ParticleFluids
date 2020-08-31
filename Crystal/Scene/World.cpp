#include "World.h"

#include "PointShaderScene.h"
#include "LightScene.h"
#include "MaterialScene.h"
#include "TextureScene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

World::World() :
	sceneIdProvider(1)
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
		scenes[1]->addScene(new LightScene(getNextSceneId(), "Light0", std::move(light)));
		//scenes[1]->addScene(sceneFactory.createLightScene(std::move(light), "Light0"));
	}

	{
		auto material = std::make_unique<Material>();
		material->ambient = ColorRGBAf(1, 1, 1, 1);
		material->diffuse = ColorRGBAf(1, 1, 1, 1);
		material->specular = ColorRGBAf(1, 1, 1, 1);
		material->shininess = 1.0;
		material->ambientTexName = "WhiteTex";
		scenes[1]->addScene(new MaterialScene(getNextSceneId(), "WhiteMat", std::move(material)));
	}

	{
		auto material = std::make_unique<Material>();
		material->ambient = ColorRGBAf(1, 0, 0, 1);
		material->diffuse = ColorRGBAf(0, 0, 0, 1);
		material->specular = ColorRGBAf(0, 0, 0, 1);
		material->shininess = 1.0;
		scenes[1]->addScene(new MaterialScene(getNextSceneId(),"RedMat", std::move(material)));
	}

	{
		auto material = std::make_unique<Material>();
		material->ambient = ColorRGBAf(0, 0, 0, 1);
		material->diffuse = ColorRGBAf(0, 0, 0, 1);
		material->specular = ColorRGBAf(0, 0, 0, 1);
		material->shininess = 1.0;
		scenes[1]->addScene(new MaterialScene(getNextSceneId(), "BlackMat", std::move(material)));
	}

	{
		auto image = std::make_unique<Image>(2,2);
		image->setColor(0, 0, ColorRGBAuc(255, 0, 0, 255));
		image->setColor(0, 1, ColorRGBAuc(0, 255, 0, 255));
		image->setColor(1, 0, ColorRGBAuc(0, 255, 255, 255));
		image->setColor(1, 1, ColorRGBAuc(0, 0, 0, 255));

//		auto tex = glFactory.getTextureFactory()->createTextureObject(image);
//		auto s = sceneFactory.createTextureScene(std::move(image), "WhiteTex");
		auto s = new TextureScene(getNextSceneId(), std::move(image), "WhiteTex");

//		s->build();
		scenes[1]->addScene(s);
	}

	{
		auto image = std::make_unique<Image>(1, 1);
		image->setColor(0, 0, ColorRGBAuc(0, 0, 0, 0));
		auto s = new TextureScene(getNextSceneId(), std::move(image), "BlackTex");
//		s->build();
		scenes[1]->addScene(s);
	}

	{
		auto c = new Camera(
			Vector3df(0, 0, 0),
			Vector3df(0, 0, -10.0),
			Vector3df(0, 0, 1),
			1.0f, 10.0f);
		camera = new CameraScene(getNextSceneId(), "MainCamera", c);

		scenes[1]->addScene(camera);
	}

	renderer = std::make_unique<SceneShader>();

}

void World::clear()
{
	glFactory.clear();
	sceneIdProvider.reset(1);
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
