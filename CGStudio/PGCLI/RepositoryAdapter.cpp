#include "stdafx.h"
#include <msclr/marshal_cppstd.h>

#include "RepositoryAdapter.h"
#include "SceneAdapter.h"

#include "../../Crystal/Scene/World.h"
//#include "../../Crystal/UI/ViewModel.h"

#include "../../Crystal/IO/FileImporter.h"
#include "../../Crystal/IO/FileExporter.h"

#include "Converter.h"


using namespace PG::CLI;

RepositoryAdapter::RepositoryAdapter() :
	instance(new Crystal::Scene::World())
{
}

RepositoryAdapter::~RepositoryAdapter()
{
	instance->clear();
	delete instance;
}

void RepositoryAdapter::Clear()
{
	instance->clear();
}

void RepositoryAdapter::Init()
{
	instance->init();
}

SceneAdapter^ RepositoryAdapter::GetSceneAdapter()
{
	return gcnew SceneAdapter(instance->getObjects(), instance->getObjectFactory());
}

SceneAdapter^ RepositoryAdapter::GetItemAdapter()
{
	return gcnew SceneAdapter(instance->getItems(), instance->getItemFactory());
}
