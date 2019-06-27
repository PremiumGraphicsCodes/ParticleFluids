#include "stdafx.h"
#include "AppearanceObjectRepositoryAdapter.h"
#include "../../Crystal/Scene/AppearanceObjectRepository.h"
#include "../../Crystal/Scene/ObjectRepository.h"
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
