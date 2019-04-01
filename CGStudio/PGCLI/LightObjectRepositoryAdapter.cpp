#include "stdafx.h"
#include "LightObjectRepositoryAdapter.h"
#include "../../Crystal/UI/LightObjectRepository.h"
#include "Converter.h"

using namespace PG::CLI;

LightObjectRepositoryAdapter::LightObjectRepositoryAdapter()
{
	this->instance = new Crystal::UI::LightObjectRepository();
}

LightObjectRepositoryAdapter::~LightObjectRepositoryAdapter()
{
	delete instance;
}

int LightObjectRepositoryAdapter::Add(PG::Core::Graphics::PointLight^ light)
{
//	instance->add( Converter::toCpp((light), "" );
	return -1;
}

LightObjectRepositoryAdapter::LightObjectRepositoryAdapter(Crystal::UI::LightObjectRepository* instance)
{
	this->instance = instance;
}
