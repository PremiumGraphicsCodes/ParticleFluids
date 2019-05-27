#pragma once

#include "../Util/UnCopyable.h"
#include "Vertex.h"
#include "VertexFactory.h"
#include "Face.h"
#include "../Math/Quaternion.h"
#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"
#include "../Math/Triangle3d.h"

#include "IShape.h"

#include <list>

namespace Crystal {
	namespace Shape {

class Vertex;
class Face;

class PolygonMesh : public IShape
{
public:
	struct Group
	{
		int materialId;
		std::list<Face*> faces;
	};

	PolygonMesh()
	{}

	PolygonMesh(VertexFactory&& vertices, const std::list<Face*>& faces);

	~PolygonMesh();

	std::list<Face*> getFaces() const { return faces; }

	std::vector<Vertex*> getVertices() const;

	std::list<HalfEdge*> getEdges() const;

	void clear();

	void add(Face* f);

	bool has(Face* f);

	bool has(HalfEdge* e);

	bool has(Vertex* v);

	void remove(Face* f);

	Math::Vector3dd getCenter() const;

	void move(const Math::Vector3dd& v) override;

	void transform(const Math::Matrix3dd& m) override;

	void transform(const Math::Matrix4dd& m) override;

private:
	VertexFactory vertices;
	std::list<Face*> faces;
};

	}
}