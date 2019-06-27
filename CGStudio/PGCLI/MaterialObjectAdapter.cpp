#include "stdafx.h"
#include "../../Crystal/Scene/MaterialObject.h"

#include "Converter.h"

#include "MaterialObjectAdapter.h"

using namespace Crystal::Model;
using namespace PG::CLI;

MaterialObjectAdapter::~MaterialObjectAdapter()
{
}

int MaterialObjectAdapter::GetId()
{
	return instance->getId();
}

System::String^ MaterialObjectAdapter::GetName()
{
	const auto& name = instance->getName();
	return msclr::interop::marshal_as<System::String^>(name);
}

bool MaterialObjectAdapter::GetVisible()
{
	return instance->isVisible();
}

void MaterialObjectAdapter::SetVisible(bool visible)
{
	instance->setVisible(visible);
}

void MaterialObjectAdapter::Update(PG::Core::Graphics::Material^ material)
{
	auto m = instance->getMaterial();
	m->ambient = Converter::toCpp(material->Ambient);
	m->diffuse = Converter::toCpp(material->Diffuse);
	m->specular = Converter::toCpp(material->Specular);
	m->shininess = material->Shininess;
}

PG::Core::Graphics::Material^ MaterialObjectAdapter::GetValue()
{
	PG::Core::Graphics::Material^ result = gcnew PG::Core::Graphics::Material();
	auto m = instance->getMaterial();
	result->Ambient = Converter::fromCpp(m->ambient);
	result->Diffuse = Converter::fromCpp(m->diffuse);
	result->Specular = Converter::fromCpp(m->specular);
	result->Shininess = m->shininess;
	return result;
}


MaterialObjectAdapter::MaterialObjectAdapter(Crystal::Model::MaterialObject* instance)
{
	this->instance = instance;
}
