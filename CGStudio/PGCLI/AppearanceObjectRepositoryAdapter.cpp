#include "stdafx.h"
#include "AppearanceObjectRepositoryAdapter.h"
#include "../../Crystal/UI/ObjectRepository.h"

using namespace PG::CLI;

AppearanceObjectRepositoryAdapter::~AppearanceObjectRepositoryAdapter()
{}

AppearanceObjectRepositoryAdapter::AppearanceObjectRepositoryAdapter(Crystal::UI::AppearanceObjectRepository* instance)
{
	this->instance = instance;
}
