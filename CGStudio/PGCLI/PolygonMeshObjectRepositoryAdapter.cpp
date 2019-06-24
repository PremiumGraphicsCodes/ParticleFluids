#include "stdafx.h"

#include "PolygonMeshObjectRepositoryAdapter.h"
#include "PolygonMeshObjectAdapter.h"
#include "../../Crystal/Model/PolygonMeshObjectRepository.h"

#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Shape/PolygonMeshBuilder.h"

#include "Converter.h"


using namespace PG::CLI;

PolygonMeshObjectRepositoryAdapter::~PolygonMeshObjectRepositoryAdapter()
{
	Clear();
}

void PolygonMeshObjectRepositoryAdapter::Clear()
{
	instance->clear();
}

int PolygonMeshObjectRepositoryAdapter::AddPolygonMesh(PG::Core::Shape::PolygonMesh^ src, System::String^ name)
{
	auto vertices = src->Vertices;

	/*
	Crystal::Shape::PolygonMeshBuilder builder;
	auto vertexFactory = builder.getVertexFactory();
	for (int i = 0; i < vertices->Count; ++i) {
		auto p = vertexFactory->createPosition(Converter::toCpp(vertices[i]->Position));
		auto n = vertexFactory->createNormal(Converter::toCpp(vertices[i]->No))
		vs.push_back()
	}
	*/
	/*
	auto triangles = src->Triangles;
	std::vector<Crystal::Math::Triangle3d> ts;
	for (int i = 0; i < triangles->Count; ++i) {
		const auto& t = Converter::toCpp(triangles[i]);
		ts.push_back(t);
	}

	builder.
	//auto polygonMesh = new Crystal::Shape::PolygonMesh()
	*/

	return -1;
}

System::Collections::Generic::List<PolygonMeshObjectAdapter^>^ PolygonMeshObjectRepositoryAdapter::GetObjects()
{
	auto results = gcnew System::Collections::Generic::List<PolygonMeshObjectAdapter^>();
	const auto& objects = instance->getObjects();
	for (const auto& o : objects) {
		results->Add(gcnew PolygonMeshObjectAdapter(o));
	}
	return results;
}

PolygonMeshObjectAdapter^ PolygonMeshObjectRepositoryAdapter::GetObjectById(int id)
{
	auto object = instance->findObjectById(id);
	if (object == nullptr) {
		return nullptr;
	}
	return gcnew PolygonMeshObjectAdapter(object);
}

PolygonMeshObjectRepositoryAdapter::PolygonMeshObjectRepositoryAdapter(Crystal::Model::PolygonMeshObjectRepository* instance)
{
	this->instance = instance;
}
