#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Util/UnCopyable.h"

#include <memory>

namespace Crystal {
	namespace Shape {
		class PolygonMesh;
	}
	namespace VDB {
		class PolygonMeshImpl;

class PolygonMesh : private UnCopyable
{
public:
	PolygonMesh();

	~PolygonMesh();

	void addVertex(const Math::Vector3df& position);

	Math::Vector3df getVertex(const int index);

	std::vector<Math::Vector3df> getVerticesf() const;

	std::vector<Math::Vector3dd> getVerticesd() const;

	void addTriangle(const std::array<int, 3>& indices);

	std::vector<std::array<unsigned int, 3>> getTriangles() const;

	void addQuad(const std::array<int, 4>& indices);

	std::vector<std::array<unsigned int, 4>> getQuads() const;

	//void fromCrystal(const Crystal::Shape::PolygonMesh& src);

	std::unique_ptr<Crystal::Shape::PolygonMesh> toCrystal() const;

	PolygonMeshImpl* getImpl() const { return impl; }

private:
	PolygonMeshImpl* impl;
};

	}
}