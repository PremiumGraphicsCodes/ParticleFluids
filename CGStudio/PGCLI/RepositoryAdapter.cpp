#include "stdafx.h"
#include <msclr/marshal_cppstd.h>

#include "RepositoryAdapter.h"

#include "../../Crystal/UI/Repository.h"
//#include "../../Crystal/UI/ViewModel.h"

#include "Converter.h"



using namespace PG::CLI;

RepositoryAdapter::RepositoryAdapter() :
	instance(new Crystal::UI::Repository())
{
}

RepositoryAdapter::~RepositoryAdapter()
{
	delete instance;
}

void RepositoryAdapter::Clear()
{
	instance->clear();
}

bool RepositoryAdapter::Read(System::String^ filename)
{
	//msclr::interop::marshal_as<std::string>(filename)
	std::string str = msclr::interop::marshal_as<std::string>(filename);
	return instance->read( str );
}

bool RepositoryAdapter::Write(System::String^ filename)
{
	std::string str = msclr::interop::marshal_as<std::string>(filename);
	return instance->write(str);
}

int RepositoryAdapter::AddParticleSystem(PG::Core::Shape::ParticleSystem^ src)
{
	auto positions = src->Positions;
	std::vector<Crystal::Math::Vector3df> ps;
	for (int i = 0; i < positions->Count; ++i) {
		const auto& p = Converter::toCpp(positions[i]);
		ps.push_back(p);
	}
	return instance->getObjects()->getParticleSystems()->addObject(ps, Crystal::Graphics::ColorRGBAf(1, 0, 0, 0), 1.0f, "");
}

int RepositoryAdapter::AddWireFrame(PG::Core::Shape::WireFrame^ src)
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

int RepositoryAdapter::AddPolygonMesh(PG::Core::Shape::PolygonMesh^ src)
{
	return -1;
}
