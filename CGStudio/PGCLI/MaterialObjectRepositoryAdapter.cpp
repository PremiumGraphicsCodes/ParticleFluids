#include "stdafx.h"
#include "MaterialObjectRepositoryAdapter.h"
#include "MaterialObjectAdapter.h"
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

System::Collections::Generic::List<MaterialObjectAdapter^>^ MaterialObjectRepositoryAdapter::GetObjects()
{
	auto results = gcnew System::Collections::Generic::List<MaterialObjectAdapter^>();
	const auto& materials = this->instance->getMaterials();
	for (const auto& m : materials) {
		results->Add(gcnew MaterialObjectAdapter(m));
	}
	return results;
}


MaterialObjectRepositoryAdapter::MaterialObjectRepositoryAdapter(Crystal::Model::MaterialObjectRepository* instance)
{
	this->instance = instance;
}
