#include "stdafx.h"
#include <msclr/marshal_cppstd.h>

#include "RepositoryAdapter.h"

#include "ObjectRepositoryAdapter.h"

#include "../../Crystal/UI/Repository.h"
//#include "../../Crystal/UI/ViewModel.h"

#include "Converter.h"



using namespace PG::CLI;

RepositoryAdapter::RepositoryAdapter() :
	instance(new Crystal::UI::Repository())
{
	objects = gcnew ObjectRepositoryAdapter(instance->getObjects());
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

bool RepositoryAdapter::Read(System::String^ filename)
{
	//msclr::interop::marshal_as<std::string>(filename)
	std::string str = msclr::interop::marshal_as<std::string>(filename);
	return instance->read( str );
}

bool RepositoryAdapter::Write(System::String^ filename)
{
	std::string str = msclr::interop::marshal_as<std::string>(filename);
	return instance->write(str);
}
