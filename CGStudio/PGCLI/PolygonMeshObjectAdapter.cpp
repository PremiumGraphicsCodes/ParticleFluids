#include "stdafx.h"
#include "../../Crystal/Scene/PolygonMeshObject.h"

#include "PolygonMeshObjectAdapter.h"
#include "Converter.h"

using namespace Crystal::Math;
using namespace PG::CLI;

PolygonMeshObjectAdapter::~PolygonMeshObjectAdapter(void)
{
}

/*
PG::Core::Shape::PolygonFace^ PolygonMeshObjectAdapter::GetFaceById(int id)
{
	auto f = instance->getShape()->findFaceById(id);
	if (f == nullptr) {
		return nullptr;
	}
	auto vs = instance->getShape()->getVertices();
	vs[f->getV1()->getId()];
	auto result = gcnew PG::Core::Shape::PolygonFace(f->getV1(), );
}
*/

int PolygonMeshObjectAdapter::GetAttributeIdById(int id)
{
	auto f = instance->getShape()->findFaceById(id);
	if (f == nullptr) {
		return -1;
	}
	auto g = instance->getShape()->findGroupByFace(f);
	return g.attributeId;
}


PolygonMeshObjectAdapter::PolygonMeshObjectAdapter(Crystal::Model::PolygonMeshObject* inst) :
	ObjectAdapter(inst)
{
	this->instance = inst;
}
