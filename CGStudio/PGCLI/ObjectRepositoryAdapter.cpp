#include "stdafx.h"
#include "ObjectRepositoryAdapter.h"
#include "../../Crystal/UI/ObjectRepository.h"

using namespace PG::CLI;

ObjectRepositoryAdapter::ObjectRepositoryAdapter()
{}

ObjectRepositoryAdapter::~ObjectRepositoryAdapter()
{}

int ObjectRepositoryAdapter::AddWireFrameObject()
{
	return 0;
}

ObjectRepositoryAdapter::ObjectRepositoryAdapter(Crystal::UI::ObjectRepository* instance)
{
	this->instance = instance;
}
