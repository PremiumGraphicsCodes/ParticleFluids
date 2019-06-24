#include "stdafx.h"
#include "../../Crystal/Model/PolygonMeshObject.h"

#include "PolygonMeshObjectAdapter.h"
#include "Converter.h"

using namespace Crystal::Math;
using namespace PG::CLI;

PolygonMeshObjectAdapter::~PolygonMeshObjectAdapter(void)
{
}

PolygonMeshObjectAdapter::PolygonMeshObjectAdapter(Crystal::Model::PolygonMeshObject* inst) :
	ObjectAdapter(inst)
{
	this->instance = inst;
}
