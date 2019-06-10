#include "stdafx.h"
#include "../../Crystal/Model/MaterialObject.h"

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

MaterialObjectAdapter::MaterialObjectAdapter(Crystal::Model::MaterialObject* instance)
{
	this->instance = instance;
}
