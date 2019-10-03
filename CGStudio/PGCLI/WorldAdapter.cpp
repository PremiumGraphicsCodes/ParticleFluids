#include "stdafx.h"
#include <msclr/marshal_cppstd.h>

#include "WorldAdapter.h"
#include "SceneAdapter.h"

#include "../../Crystal/Scene/World.h"
//#include "../../Crystal/UI/ViewModel.h"

#include "../../Crystal/IO/FileImporter.h"
#include "../../Crystal/IO/FileExporter.h"

#include "Converter.h"


using namespace PG::CLI;

WorldAdapter::WorldAdapter() :
	instance(new Crystal::Scene::World())
{
}

WorldAdapter::~WorldAdapter()
{
	instance->clear();
	delete instance;
}

void WorldAdapter::Clear()
{
	instance->clear();
}

void WorldAdapter::Init()
{
	instance->init();
}