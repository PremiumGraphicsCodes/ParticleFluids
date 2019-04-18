#include "stdafx.h"
#include "MaterialObjectRepositoryAdapter.h"
#include "../../Crystal/Model/MaterialObjectRepository.h"
#include "Converter.h"

using namespace PG::CLI;

MaterialObjectRepositoryAdapter::MaterialObjectRepositoryAdapter()
{
	this->instance = new Crystal::Model::MaterialObjectRepository();
}

MaterialObjectRepositoryAdapter::~MaterialObjectRepositoryAdapter()
{}

int MaterialObjectRepositoryAdapter::Add(PG::Core::Graphics::Material^ material)
{
	return -1;
	//	instance->add( Converter::toCpp((light), "" );
}

MaterialObjectRepositoryAdapter::MaterialObjectRepositoryAdapter(Crystal::Model::MaterialObjectRepository* instance)
{
	this->instance = instance;
}
