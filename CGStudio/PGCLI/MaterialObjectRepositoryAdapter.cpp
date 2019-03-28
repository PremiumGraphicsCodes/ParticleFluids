#include "stdafx.h"
#include "MaterialObjectRepositoryAdapter.h"
#include "../../Crystal/UI/MaterialObjectRepository.h"
#include "Converter.h"

using namespace PG::CLI;

MaterialObjectRepositoryAdapter::~MaterialObjectRepositoryAdapter()
{}

void MaterialObjectRepositoryAdapter::Add(PG::Core::Graphics::Material^ material)
{
	//	instance->add( Converter::toCpp((light), "" );
}

MaterialObjectRepositoryAdapter::MaterialObjectRepositoryAdapter(Crystal::UI::MaterialObjectRepository* instance)
{
	this->instance = instance;
}
