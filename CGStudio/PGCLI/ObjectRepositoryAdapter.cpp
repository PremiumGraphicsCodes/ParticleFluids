#include "stdafx.h"
#include "ObjectRepositoryAdapter.h"
#include "../../Crystal/Model/ObjectRepository.h"

#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Shape/PolygonMeshBuilder.h"

#include "Converter.h"

using namespace PG::CLI;

ObjectRepositoryAdapter::~ObjectRepositoryAdapter()
{}

int ObjectRepositoryAdapter::AddParticleSystem(PG::Core::Shape::ParticleSystem^ src, PG::Core::UI::ParticleAppearance^ appearance)
{
	auto positions = src->Positions;
	std::vector<Crystal::Math::Vector3dd> ps;
	for (int i = 0; i < positions->Count; ++i) {
		const auto& p = Converter::toCpp(positions[i]);
		ps.push_back(p);
	}
	Crystal::Model::ParticleAttribute attr;
	attr.color = Converter::toCpp(appearance->Color);
	attr.size = appearance->Size;
	return instance->getParticleSystems()->addObject(ps, attr, "");
}

int ObjectRepositoryAdapter::AddWireFrame(PG::Core::Shape::WireFrame^ src, PG::Core::UI::WireAppearance^ appearance)
{
	auto edges = src->Edges;
	std::vector<Crystal::Math::Line3dd> ls;
	for (int i = 0; i < edges->Count; ++i) {
		const auto& l = Converter::toCpp(edges[i]->ToLine());
		ls.push_back(l);
	}
	Crystal::Shape::WireFrame* wf = new Crystal::Shape::WireFrame(ls);
	Crystal::Model::WireFrameAttribute attr;
	attr.width = 1.0;
	attr.color = Crystal::Graphics::ColorRGBAf(1, 0, 0, 0);
	return instance->getWireFrames()->addObject(wf, attr, "");
}

int ObjectRepositoryAdapter::AddPolygonMesh(PG::Core::Shape::PolygonMesh^ src)
{
	/*
	auto triangles = src->Triangles;
	std::vector<Crystal::Math::Triangle3d> ts;
	for (int i = 0; i < triangles->Count; ++i) {
		const auto& t = Converter::toCpp(triangles[i]);
		ts.push_back(t);
	}
	
	Crystal::Shape::PolygonMeshBuilder builder;
	builder.
	//auto polygonMesh = new Crystal::Shape::PolygonMesh()
	*/

	return -1;
}

ObjectRepositoryAdapter::ObjectRepositoryAdapter(Crystal::Model::ObjectRepository* instance)
{
	this->instance = instance;

}
