#pragma once

using namespace System;

namespace Crystal {
	namespace UI {
		class Model;
	}
}

namespace PG {
	namespace CLI {

public ref class Model
{
public:
	Model();

	~Model(void);

	int AddParticleSystem(PG::Shape::ParticleSystem^ src);

	int AddWireFrame(PG::Shape::WireFrame^ src);

	int AddPolygonMesh(PG::Shape::PolygonMesh^ src);

internal:
	Crystal::UI::Model* instance;
};

	}
}
