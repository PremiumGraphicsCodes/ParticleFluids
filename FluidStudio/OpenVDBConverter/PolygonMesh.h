#pragma once

#include "../../Crystal/Util/UnCopyable.h"

namespace Crystal {
	namespace OpenVDB {
		class PolygonMeshImpl;

class PolygonMesh : private UnCopyable
{
public:
	PolygonMesh();

	~PolygonMesh();

	const PolygonMeshImpl* getImpl() const { return impl; }

private:
	PolygonMeshImpl* impl;
};

	}
}