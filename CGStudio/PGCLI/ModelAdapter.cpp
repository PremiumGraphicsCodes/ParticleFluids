#include "stdafx.h"
#include <msclr/marshal_cppstd.h>

#include "ModelAdapter.h"

#include "../../Crystal/UI/Model.h"
#include "../../Crystal/UI/ViewModel3d.h"

#include "Converter.h"



using namespace PG::CLI;

ModelAdapter::ModelAdapter() :
	instance(new Crystal::UI::Model())
{
}

ModelAdapter::~ModelAdapter()
{
	delete instance;
}

void ModelAdapter::Clear()
{
	instance->clear();
}

bool ModelAdapter::Read(System::String^ filename)
{
	//msclr::interop::marshal_as<std::string>(filename)
	std::string str = msclr::interop::marshal_as<std::string>(filename);
	return instance->read( str );
}

bool ModelAdapter::Write(System::String^ filename)
{
	std::string str = msclr::interop::marshal_as<std::string>(filename);
	return instance->write(str);
}

int ModelAdapter::AddParticleSystem(PG::Core::Shape::ParticleSystem^ src)
{
	auto positions = src->Positions;
	std::vector<Crystal::Math::Vector3df> ps;
	for (int i = 0; i < positions->Count; ++i) {
		const auto& p = Converter::toCpp(positions[i]);
		ps.push_back(p);
	}
	return instance->getObjects()->getParticleSystems()->addObject(ps, Crystal::Graphics::ColorRGBAf(1, 0, 0, 0), 1.0f, "");
}

int ModelAdapter::AddWireFrame(PG::Core::Shape::WireFrame^ src)
{
	auto lines = src->Lines;
	std::vector<Crystal::Math::Line3dd> ls;
	for (int i = 0; i < lines->Count; ++i) {
		const auto& l = Converter::toCpp(lines[i]);
		ls.push_back(l);
	}
	Crystal::Shape::WireFrame* wf = new Crystal::Shape::WireFrame(ls);
	return instance->getObjects()->getWireFrames()->addObject(wf, Crystal::Graphics::ColorRGBAf(1, 0, 0, 0), "");
}

int ModelAdapter::AddPolygonMesh(PG::Core::Shape::PolygonMesh^ src)
{
	return -1;
}
