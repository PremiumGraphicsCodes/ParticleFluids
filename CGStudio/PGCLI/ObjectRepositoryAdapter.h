#pragma once

using namespace System;

namespace Crystal {
	namespace UI {
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
	ObjectRepositoryAdapter(Crystal::UI::ObjectRepository* instance);

	Crystal::UI::ObjectRepository* instance;
};

	}
}