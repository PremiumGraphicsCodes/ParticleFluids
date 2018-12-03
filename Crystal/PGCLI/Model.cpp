#include "stdafx.h"
#include "Model.h"

#include "../UI/IModel.h"
#include "../UI/ViewModel3d.h"

#include "Converter.h"

using namespace PG::CLI;

Model::Model() :
	instance(new Crystal::UI::IModel()),
	viewModel(new Crystal::UI::ViewModel3d())
{
}

Model::~Model()
{
	delete viewModel;
	delete instance;
}

int Model::AddParticleSystem(PG::Core::Shape::ParticleSystem^ src)
{
	auto positions = src->Positions;
	std::vector<Crystal::Math::Vector3df> ps;
	for (int i = 0; i < positions->Count; ++i) {
		const auto& p = Convereter::toCpp(positions[i]);
		ps.push_back(p);
	}
	return instance->getRepository()->addParticleSystem(ps, Crystal::Graphics::ColorRGBAf(1, 0, 0, 0), 1.0f);
}

int Model::AddWireFrame(PG::Core::Shape::WireFrame^ src)
{
	return -1;
}

int Model::AddPolygonMesh(PG::Core::Shape::PolygonMesh^ src)
{
	return -1;
}
