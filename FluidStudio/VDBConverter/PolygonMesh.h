#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Util/UnCopyable.h"

namespace Crystal {
	namespace Shape {
		class PolygonMesh;
	}
	namespace OpenVDB {
		class PolygonMeshImpl;

class PolygonMesh : private UnCopyable
{
public:
	PolygonMesh();

	//PolygonMesh(PolygonMesh&& rhs);

	//PolygonMesh& operator=(const PolygonMesh&& rhs);

	~PolygonMesh();

	void addVertex(const Math::Vector3df& position);

	Math::Vector3df getVertex(const int index);

	std::vector<Math::Vector3df> getVertices() const;

	void addTriangle(const std::array<int, 3>& indices);

	std::array<unsigned int, 3> getTriangle(const int index) const;

	void addQuad(const std::array<int, 4>& indices);

	std::vector<std::array<unsigned int, 4>> getQuads() const;

	//void fromCrystal(const Crystal::Shape::PolygonMesh& src);

	//Crystal::Shape::PolygonMesh toCrystal() const;

	PolygonMeshImpl* getImpl() const { return impl; }

private:
	PolygonMeshImpl* impl;
};

	}
}