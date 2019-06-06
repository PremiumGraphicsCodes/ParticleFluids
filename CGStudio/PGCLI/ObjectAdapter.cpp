#include "stdafx.h"
#include "../../Crystal/Model/IObject.h"

#include "ObjectAdapter.h"

using namespace Crystal::Model;
using namespace PG::CLI;

ObjectAdapter::~ObjectAdapter()
{
}

int ObjectAdapter::GetId()
{
	return instance->getId();
}

System::String^ ObjectAdapter::GetName()
{
	const auto& name = instance->getName();
	return msclr::interop::marshal_as<System::String^>(name);
}

bool ObjectAdapter::GetVisible()
{
	return instance->isVisible();
}

void ObjectAdapter::SetVisible(bool visible)
{
	instance->setVisible(visible);
}

ObjectAdapter::ObjectAdapter(Crystal::Model::IObject* instance)
{
	this->instance = instance;
}
