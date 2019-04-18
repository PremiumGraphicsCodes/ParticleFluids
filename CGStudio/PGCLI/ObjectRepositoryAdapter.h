#pragma once

using namespace System;

namespace Crystal {
	namespace Model {
		class ObjectRepository;
	}
}

namespace PG {
	namespace CLI {

public ref class ObjectRepositoryAdapter
{
public:
	~ObjectRepositoryAdapter(void);

	int AddParticleSystem(PG::Core::Shape::ParticleSystem^ src, PG::Core::UI::ParticleAppearance^ appearance);

	int AddWireFrame(PG::Core::Shape::WireFrame^ src, PG::Core::UI::WireAppearance^ appearance);

	int AddPolygonMesh(PG::Core::Shape::PolygonMesh^ src);

internal:
	ObjectRepositoryAdapter(Crystal::Model::ObjectRepository* instance);

	Crystal::Model::ObjectRepository* instance;
};

	}
}