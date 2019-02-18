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

internal:
	Crystal::UI::Repository* instance;
};

	}
}
