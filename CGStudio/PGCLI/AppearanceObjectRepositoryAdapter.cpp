#include "stdafx.h"
#include "AppearanceObjectRepositoryAdapter.h"
#include "../../Crystal/UI/AppearanceObjectRepository.h"
#include "../../Crystal/UI/ObjectRepository.h"

using namespace PG::CLI;

AppearanceObjectRepositoryAdapter::AppearanceObjectRepositoryAdapter()
{
	this->instance = new Crystal::UI::AppearanceObjectRepository();
}

AppearanceObjectRepositoryAdapter::~AppearanceObjectRepositoryAdapter()
{
	delete instance;
}

AppearanceObjectRepositoryAdapter::AppearanceObjectRepositoryAdapter(Crystal::UI::AppearanceObjectRepository* instance)
{
	this->instance = instance;
}
