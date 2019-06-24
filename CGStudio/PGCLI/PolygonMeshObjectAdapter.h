#pragma once

#include "ObjectAdapter.h"

using namespace System;

namespace Crystal {
	namespace Model {
		class PolygonMeshObject;
	}
}

namespace PG {
	namespace CLI {

public ref class PolygonMeshObjectAdapter : public ObjectAdapter
{
public:
	~PolygonMeshObjectAdapter(void);

	int GetFaceById(int id);

internal:
	PolygonMeshObjectAdapter(Crystal::Model::PolygonMeshObject* instance);

	Crystal::Model::PolygonMeshObject* instance;
};

	}
}