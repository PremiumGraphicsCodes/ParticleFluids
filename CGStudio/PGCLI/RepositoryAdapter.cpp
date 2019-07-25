#include "stdafx.h"
#include <msclr/marshal_cppstd.h>

#include "RepositoryAdapter.h"
#include "SceneAdapter.h"

#include "../../Crystal/UI/Repository.h"
//#include "../../Crystal/UI/ViewModel.h"

#include "Converter.h"



using namespace PG::CLI;

RepositoryAdapter::RepositoryAdapter() :
	instance(new Crystal::UI::Repository())
{
}

RepositoryAdapter::~RepositoryAdapter()
{
	instance->clear();
	delete instance;
}

void RepositoryAdapter::Clear()
{
	instance->clear();
}

void RepositoryAdapter::Init()
{
	instance->init();
}

bool RepositoryAdapter::Import(System::String^ filename)
{
	if (filename == nullptr) {
		return false;
	}
	const auto& str = msclr::interop::marshal_as<std::wstring>(filename);
	return instance->importFile( str );
}

bool RepositoryAdapter::Export(System::String^ filename)
{
	if (filename == nullptr) {
		return false;
	}

	const auto& str = msclr::interop::marshal_as<std::wstring>(filename);
	return instance->exportFile(str);
}

SceneAdapter^ RepositoryAdapter::GetSceneAdapter()
{
	return gcnew SceneAdapter(instance->getObjects(), instance->getObjectFactory());
}

SceneAdapter^ RepositoryAdapter::GetItemAdapter()
{
	return gcnew SceneAdapter(instance->getItems(), instance->getItemFactory());
}
