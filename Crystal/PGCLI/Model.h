#pragma once

using namespace System;

namespace Crystal {
	namespace UI {
		class IModel;
		class ViewModel3d;
	}
}

namespace PG {
	namespace CLI {

public ref class Model
{
public:
	Model();

	~Model(void);

	int AddParticleSystem(PG::Core::Shape::ParticleSystem^ src);

	int AddWireFrame(PG::Core::Shape::WireFrame^ src);

	int AddPolygonMesh(PG::Core::Shape::PolygonMesh^ src);

internal:
	Crystal::UI::IModel* instance;
};

	}
}
