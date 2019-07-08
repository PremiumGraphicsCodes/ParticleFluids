#include "stdafx.h"
#include "SceneAdapter.h"

#include "../../Crystal/Scene/Scene.h"

using namespace PG::CLI;
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
	return -1;
}

int SceneAdapter::AddWireFrameScene(System::Collections::Generic::List<PG::Core::Math::Line3d^>^ positions)
{
	return -1;
}

int SceneAdapter::AddPolygonMeshScene(System::Collections::Generic::List<PG::Core::Math::Line3d^>^ positions)
{
	return -1;
}

SceneAdapter::SceneAdapter(Crystal::Scene::Scene* instance) :
	instance(instance)
{
}
