#include "stdafx.h"
#include "../../Crystal/Scene/IScene.h"

#include "ObjectAdapter.h"
#include "Converter.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

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
//	instance->move(Converter::toCpp(v));
}

void ObjectAdapter::Transform(PG::Core::Math::Matrix3d^ m)
{
//	instance->transform(Converter::toCpp(m));
}

void ObjectAdapter::Transform(PG::Core::Math::Matrix4d^ m)
{
//	instance->transform(Converter::toCpp(m));
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

PG::Core::Shape::ShapeType ObjectAdapter::GetType()
{
	const auto type = instance->getType();
	switch (type) {
	case Crystal::Model::SceneType::ParticleSystemScene :
		return PG::Core::Shape::ShapeType::ParticleSystem;
	case Crystal::Model::SceneType::WireFrameScene :
		return PG::Core::Shape::ShapeType::WireFrame;
	case Crystal::Model::SceneType::PolygonMeshScene :
		return PG::Core::Shape::ShapeType::PolygonMesh;
	default:
		assert(false);
	}
	return PG::Core::Shape::ShapeType::None;
}

PG::Core::Math::Vector3d^ ObjectAdapter::GetPositionById(int id)
{
	const auto type = instance->getType();
	if (type == Crystal::Model::SceneType::ParticleSystemScene) {
		auto ps = static_cast<Crystal::Model::ParticleSystemScene*>(instance);
		const auto& particles = ps->getShape()->getParticles();
		return Converter::fromCpp( particles[id]->getPosition() );
	}
	return nullptr;
}


ObjectAdapter::ObjectAdapter(Crystal::Model::IScene* instance)
{
	this->instance = instance;
}
