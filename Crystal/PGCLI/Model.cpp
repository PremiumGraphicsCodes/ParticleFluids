#include "stdafx.h"
#include "Model.h"

#include "../UI/IModel.h"
#include "../UI/ViewModel3d.h"

#include "Converter.h"

using namespace PG::CLI;

Model::Model() :
	instance(new Crystal::UI::IModel())
{
}

Model::~Model()
{
	delete instance;
}

int Model::AddParticleSystem(PG::Core::Shape::ParticleSystem^ src)
{
	auto positions = src->Positions;
	std::vector<Crystal::Math::Vector3df> ps;
	for (int i = 0; i < positions->Count; ++i) {
		const auto& p = Converter::toCpp(positions[i]);
		ps.push_back(p);
	}
	return instance->getRepository()->addParticleSystem(ps, Crystal::Graphics::ColorRGBAf(1, 0, 0, 0), 1.0f);
}

int Model::AddWireFrame(PG::Core::Shape::WireFrame^ src)
{
	auto lines = src->Lines;
	std::vector<Crystal::Math::Line3dd> ls;
	for (int i = 0; i < lines->Count; ++i) {
		const auto& l = Converter::toCpp(lines[i]);
		ls.push_back(l);
	}
	Crystal::Shape::WireFrame* wf = new Crystal::Shape::WireFrame(ls);
	return instance->getRepository()->addWireFrame(wf, Crystal::Graphics::ColorRGBAf(1, 0, 0, 0));
}

int Model::AddPolygonMesh(PG::Core::Shape::PolygonMesh^ src)
{
	return -1;
}
