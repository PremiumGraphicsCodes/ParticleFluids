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

	int AddParticleSystem(PG::Core::Shape::ParticleSystem^ src, PG::Core::UI::ParticleAppearance^ appearance, System::String^ name);

	int AddWireFrame(PG::Core::Shape::WireFrame^ src, PG::Core::UI::WireAppearance^ appearance, System::String^ name);

	int AddPolygonMesh(PG::Core::Shape::PolygonMesh^ src, System::String^ name);

	System::Collections::Generic::List<int>^ GetAllIds();

	System::String^ GetNameById(int id);

	bool GetVisibleById(int id);

	void SetVisibleById(int id, bool visible);

internal:
	ObjectRepositoryAdapter(Crystal::Model::ObjectRepository* instance);

	Crystal::Model::ObjectRepository* instance;
};

	}
}