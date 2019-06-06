#include "stdafx.h"
#include "AppearanceObjectRepositoryAdapter.h"
#include "../../Crystal/Model/AppearanceObjectRepository.h"
#include "../../Crystal/Model/ObjectRepository.h"
#include "MaterialObjectRepositoryAdapter.h"

using namespace PG::CLI;

AppearanceObjectRepositoryAdapter::~AppearanceObjectRepositoryAdapter()
{
	delete instance;
}

AppearanceObjectRepositoryAdapter::AppearanceObjectRepositoryAdapter(Crystal::Model::AppearanceObjectRepository* instance)
{
	this->instance = instance;
}

MaterialObjectRepositoryAdapter^ AppearanceObjectRepositoryAdapter::Material()
{
	return gcnew MaterialObjectRepositoryAdapter(this->instance->getMaterials());
}
