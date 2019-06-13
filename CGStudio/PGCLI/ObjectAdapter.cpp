#include "stdafx.h"
#include "../../Crystal/Model/IObject.h"

#include "ObjectAdapter.h"
#include "Converter.h"

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

void ObjectAdapter::SetName(System::String^ name)
{
	const auto& str = msclr::interop::marshal_as<std::string>(name);
	instance->setName(str);
}

bool ObjectAdapter::GetVisible()
{
	return instance->isVisible();
}

void ObjectAdapter::SetVisible(bool visible)
{
	instance->setVisible(visible);
}

void ObjectAdapter::Move(PG::Core::Math::Vector3d^ v)
{
	instance->move(Converter::toCpp(v));
}

void ObjectAdapter::Transform(PG::Core::Math::Matrix3d^ m)
{
	instance->transform(Converter::toCpp(m));
}

void ObjectAdapter::Transform(PG::Core::Math::Matrix4d^ m)
{
	instance->transform(Converter::toCpp(m));
}


/*
void ObjectAdapter::Scale(PG::Core::Math::Vector3d^ s)
{
}

void ObjectAdapter::Rotate(double rx, double ry, double rz)
{

}
*/

bool ObjectAdapter::IsSelected()
{
	return instance->isSelected();
}

void ObjectAdapter::Select()
{
	instance->setSelected(true);
}

void ObjectAdapter::UnSelect()
{
	instance->setSelected(false);
}

void ObjectAdapter::SetSelected(bool b)
{
	instance->setSelected(b);
}


ObjectAdapter::ObjectAdapter(Crystal::Model::IObject* instance)
{
	this->instance = instance;
}
