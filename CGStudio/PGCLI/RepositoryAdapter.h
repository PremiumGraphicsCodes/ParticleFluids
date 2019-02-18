#pragma once

using namespace System;

namespace Crystal {
	namespace UI {
		class Repository;
		class ViewModel3d;
	}
}

namespace PG {
	namespace CLI {
		ref class ObjectRepositoryAdapter;

public ref class RepositoryAdapter
{
public:
	RepositoryAdapter();

	~RepositoryAdapter(void);

	void Clear();

	bool Read(System::String^ filename);

	bool Write(System::String^ filename);

	int AddParticleSystem(PG::Core::Shape::ParticleSystem^ src);

	int AddWireFrame(PG::Core::Shape::WireFrame^ src);

	int AddPolygonMesh(PG::Core::Shape::PolygonMesh^ src);

	ObjectRepositoryAdapter^ Objects() { return objects; }

private:
	ObjectRepositoryAdapter^ objects;

internal:
	Crystal::UI::Repository* instance;
};

	}
}
