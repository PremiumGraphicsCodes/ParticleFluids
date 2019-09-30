#include "stdafx.h"
#include "SceneAdapter.h"

#include "../../Crystal/Scene/Scene.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../../Crystal/Scene/WireFrameScene.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../../Crystal/Scene/SceneFactory.h"
#include "Converter.h"

using namespace PG::CLI;
using namespace Crystal::Math;
using namespace Crystal::Scene;

SceneAdapter::~SceneAdapter()
{
	Clear();
	delete instance;
}

void SceneAdapter::Clear()
{
	instance->clear();
}

int SceneAdapter::AddLightScene(PG::Core::Graphics::PointLight^ light, System::String^ name)
{
	auto l = Converter::toCpp(light);
	auto str = msclr::interop::marshal_as<std::string>(name);
	auto scene = factory->createLightScene(l, str);
	instance->addScene(scene);
	return scene->getId();
}

int SceneAdapter::AddMaterialScene(PG::Core::Graphics::Material^ material, System::String^ name)
{
	auto m = Converter::toCpp(material);
	auto str = msclr::interop::marshal_as<std::string>(name);
	auto scene = factory->createMaterialScene(m, str);
	instance->addScene(scene);
	return scene->getId();
}

void SceneAdapter::ChangeName(int id, System::String^ name)
{
	auto scene = instance->findSceneById(id);
	auto str = msclr::interop::marshal_as<std::string>(name);
	scene->setName(str);
}

void SceneAdapter::UpdateLightScene(int id, PG::Core::Graphics::PointLight^ light)
{
	auto scene = instance->findSceneById(id);
	if (scene->getType() != Crystal::Scene::SceneType::LightScene) {
		return;
	}
	auto lightScene = static_cast<Crystal::Scene::LightScene*>(scene);
	auto l = Converter::toCpp(light);
	lightScene->setLight(l);
}

void SceneAdapter::UpdateMaterialScene(int id, PG::Core::Graphics::Material^ material)
{
	auto scene = instance->findSceneById(id);
	if (scene->getType() != Crystal::Scene::SceneType::MaterialScene) {
		return;
	}
	auto materialScene = static_cast<Crystal::Scene::MaterialScene*>(scene);
	auto m = Converter::toCpp(material);
	materialScene->setMaterial(m);
}

PG::Core::Graphics::Material^ SceneAdapter::FindMaterialByid(int id)
{
	auto scene = instance->findSceneById(id);
	if (scene->getType() != Crystal::Scene::SceneType::MaterialScene) {
		return nullptr;
	}
	auto materialScene = static_cast<Crystal::Scene::MaterialScene*>(scene);
	return Converter::fromCpp(materialScene->getMaterial());
}

PG::Core::Graphics::PointLight^ SceneAdapter::FindLightById(int id)
{
	auto scene = instance->findSceneById(id);
	if (scene->getType() != Crystal::Scene::SceneType::LightScene) {
		return nullptr;
	}
	auto lightScene = static_cast<Crystal::Scene::LightScene*>(scene);
	return Converter::fromCpp(lightScene->getLight());
}

PG::Core::Math::Vector3d^ SceneAdapter::FindPositionById(int parentId, int childId)
{
	auto scene = instance->findSceneById<Crystal::Scene::IShapeScene*>(parentId);
	return Converter::fromCpp( scene->getPosition(childId) );
}


PG::Core::Scene^ SceneAdapter::ToScene()
{
	auto scene = ToScene(instance);
	return scene;
}

PG::Core::Scene^ SceneAdapter::ToScene(IScene* parent)
{
	auto str = msclr::interop::marshal_as<System::String^>(parent->getName());
	auto type = Converter::fromCpp(parent->getType());
	auto p = gcnew PG::Core::Scene(parent->getId(), str, type);

	auto children = parent->getChildren();
	for (auto child : children) {
		auto c = ToScene(child);
		p->Children->Add(c);
		ToScene(child);
	}
	return p;
}

PG::Core::SceneType^ SceneAdapter::GetTypeById(int id)
{
	auto scene = instance->findSceneById(id);
	if (scene == nullptr) {
		return PG::Core::SceneType::None;
	}
	return Converter::fromCpp(scene->getType());
}

SceneAdapter::SceneAdapter(Crystal::Scene::Scene* instance, Crystal::Scene::SceneFactory*factory) :
	instance(instance),
	factory(factory)
{

}
