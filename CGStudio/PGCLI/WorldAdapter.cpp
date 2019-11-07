#include "stdafx.h"

#include "WorldAdapter.h"

#include "../../Crystal/Scene/World.h"
//#include "../../Crystal/UI/ViewModel.h"

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

void WorldAdapter::ClearItems()
{
	instance->getItems()->clear();
}

void WorldAdapter::Init()
{
	instance->init();
}