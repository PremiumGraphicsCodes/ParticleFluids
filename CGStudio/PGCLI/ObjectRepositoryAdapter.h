#pragma once

using namespace System;

namespace Crystal {
	namespace Model {
		class ObjectRepository;
	}
}

namespace PG {
	namespace CLI {
		ref class ObjectAdapter;

public ref class ObjectRepositoryAdapter
{
public:
	virtual ~ObjectRepositoryAdapter(void);

	void Clear();

	int AddParticleSystem(PG::Core::Shape::ParticleSystem^ src, PG::Core::UI::ParticleAppearance^ appearance, System::String^ name);

	int AddWireFrame(PG::Core::Shape::WireFrame^ src, PG::Core::UI::WireAppearance^ appearance, System::String^ name);

	int AddPolygonMesh(PG::Core::Shape::PolygonMesh^ src, System::String^ name);

	System::Collections::Generic::List<ObjectAdapter^>^ GetObjects();

	ObjectAdapter^ GetObjectById(int id);

internal:
	ObjectRepositoryAdapter(Crystal::Model::ObjectRepository* instance);

	Crystal::Model::ObjectRepository* instance;
};

	}
}