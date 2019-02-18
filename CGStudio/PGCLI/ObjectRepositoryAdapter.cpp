#include "stdafx.h"
#include "ObjectRepositoryAdapter.h"
#include "../../Crystal/UI/ObjectRepository.h"

#include "Converter.h"

using namespace PG::CLI;

ObjectRepositoryAdapter::~ObjectRepositoryAdapter()
{}

int ObjectRepositoryAdapter::AddParticleSystem(PG::Core::Shape::ParticleSystem^ src)
{
	auto positions = src->Positions;
	std::vector<Crystal::Math::Vector3df> ps;
	for (int i = 0; i < positions->Count; ++i) {
		const auto& p = Converter::toCpp(positions[i]);
		ps.push_back(p);
	}
	return instance->getParticleSystems()->addObject(ps, Crystal::Graphics::ColorRGBAf(1, 0, 0, 0), 1.0f, "");
}

int ObjectRepositoryAdapter::AddWireFrame(PG::Core::Shape::WireFrame^ src)
{
	auto lines = src->Lines;
	std::vector<Crystal::Math::Line3dd> ls;
	for (int i = 0; i < lines->Count; ++i) {
		const auto& l = Converter::toCpp(lines[i]);
		ls.push_back(l);
	}
	Crystal::Shape::WireFrame* wf = new Crystal::Shape::WireFrame(ls);
	return instance->getWireFrames()->addObject(wf, Crystal::Graphics::ColorRGBAf(1, 0, 0, 0), "");
}

int ObjectRepositoryAdapter::AddPolygonMesh(PG::Core::Shape::PolygonMesh^ src)
{
	return -1;
}

ObjectRepositoryAdapter::ObjectRepositoryAdapter(Crystal::UI::ObjectRepository* instance)
{
	this->instance = instance;
}
