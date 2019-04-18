#include "stdafx.h"
#include "AppearanceObjectRepositoryAdapter.h"
#include "../../Crystal/Model/AppearanceObjectRepository.h"
#include "../../Crystal/Model/ObjectRepository.h"

using namespace PG::CLI;

AppearanceObjectRepositoryAdapter::AppearanceObjectRepositoryAdapter()
{
	this->instance = new Crystal::Model::AppearanceObjectRepository();
}

AppearanceObjectRepositoryAdapter::~AppearanceObjectRepositoryAdapter()
{
	delete instance;
}

AppearanceObjectRepositoryAdapter::AppearanceObjectRepositoryAdapter(Crystal::Model::AppearanceObjectRepository* instance)
{
	this->instance = instance;
}
