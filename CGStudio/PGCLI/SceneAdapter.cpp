#include "stdafx.h"
#include "SceneAdapter.h"

#include "../../Crystal/Scene/Scene.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"
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

bool SceneAdapter::Import(System::String^ filename)
{
	//const auto& str = msclr::interop::marshal_as<std::wstring>(filename);
	return false;
}

bool SceneAdapter::Export(System::String^ filename)
{
	return false;
}

int SceneAdapter::AddParticleSystemScene(System::Collections::Generic::List<PG::Core::Math::Vector3d^>^ positions)
{
	std::vector<Vector3dd> ps;
	for (int i = 0; i < positions->Count; ++i) {
		ps.push_back(Converter::toCpp(positions[i]));
	}
	auto scene = factory->createParticleSystemScene(ps, ParticleAttribute(), "");
	instance->addScene( scene );
	return scene->getId();
}

int SceneAdapter::AddWireFrameScene(System::Collections::Generic::List<PG::Core::Math::Line3d^>^ lines)
{
	/*
	std::vector<Line3dd> ls;
	for (int i = 0; i < lines->Count; ++i) {
		ls.push_back(Converter::toCpp(lines[i]));
	}
	factory->createWireFrameScene(ls, WireFrameAttribute(), "");
	*/
	return -1;
}

int SceneAdapter::AddPolygonMeshScene(System::Collections::Generic::List<PG::Core::Math::Line3d^>^ positions)
{
	return -1;
}

SceneAdapter::SceneAdapter(Crystal::Scene::Scene* instance, Crystal::Scene::SceneFactory*factory) :
	instance(instance),
	factory(factory)
{

}
