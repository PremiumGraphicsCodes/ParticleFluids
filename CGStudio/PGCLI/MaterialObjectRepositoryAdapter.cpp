#include "stdafx.h"
#include "MaterialObjectRepositoryAdapter.h"
#include "MaterialObjectAdapter.h"
#include "../../Crystal/Scene/MaterialObjectRepository.h"
#include "Converter.h"

using namespace PG::CLI;

MaterialObjectRepositoryAdapter::~MaterialObjectRepositoryAdapter()
{}

int MaterialObjectRepositoryAdapter::Add(PG::Core::Graphics::Material^ material, System::String^ name)
{
	auto m = Converter::toCpp(material);
	const auto& n = msclr::interop::marshal_as<std::string>(name);
	return instance->add(new Crystal::Graphics::Material(m), n);
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
