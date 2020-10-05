#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Util/UnCopyable.h"

namespace Crystal {
	namespace OpenVDB {
		class PolygonMeshImpl;

class PolygonMesh : private UnCopyable
{
public:
	PolygonMesh();

	//PolygonMesh(PolygonMesh&& rhs);

	//PolygonMesh& operator=(const PolygonMesh&& rhs);

	~PolygonMesh();

	void addVertex(const Math::Vector3dd& position);

	void addTriangle(const std::array<int, 3>& indices);

	void addQuad(const std::array<int, 4>& indices);

	PolygonMeshImpl* getImpl() const { return impl; }

private:
	PolygonMeshImpl* impl;
};

	}
}