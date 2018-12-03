#include "stdafx.h"
#include "Model.h"

#include "../UI/IModel.h"

using namespace PG::CLI;

Model::Model() :
	instance(new Crystal::UI::IModel())
{
}

Model::~Model()
{
	delete instance;
}

int Model::AddParticleSystem(PG::Shape::ParticleSystem^ src)
{
	auto positions = src->Positions;
	std::vector<Crystal::Math::Vector3df> ps;
	for (int i = 0; i < positions->Count; ++i) {
		Crystal::Math::Vector3df p(positions[i]->X, positions[i]->Y, positions[i]->Z);
		ps.push_back(p);
	}
	return instance->getRepository()->addParticleSystem(ps, Crystal::Graphics::ColorRGBAf(1, 0, 0, 0), 1.0f);
}

int Model::AddWireFrame(PG::Shape::WireFrame^ src)
{
	return -1;
}

int Model::AddPolygonMesh(PG::Shape::PolygonMesh^ src)
{
	return -1;
}
