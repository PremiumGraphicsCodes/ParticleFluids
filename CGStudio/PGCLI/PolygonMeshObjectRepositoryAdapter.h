#pragma once

using namespace System;

namespace Crystal {
	namespace Model {
		class PolygonMeshObjectRepository;
	}
}

namespace PG {
	namespace CLI {
		ref class PolygonMeshObjectAdapter;

public ref class PolygonMeshObjectRepositoryAdapter
{
public:
	virtual ~PolygonMeshObjectRepositoryAdapter(void);

	void Clear();

	int AddPolygonMesh(PG::Core::Shape::PolygonMesh^ src, System::String^ name);

	System::Collections::Generic::List<PolygonMeshObjectAdapter^>^ GetObjects();

	PolygonMeshObjectAdapter^ GetObjectById(int id);

internal:
	PolygonMeshObjectRepositoryAdapter(Crystal::Model::PolygonMeshObjectRepository* instance);

	Crystal::Model::PolygonMeshObjectRepository* instance;
};

	}
}