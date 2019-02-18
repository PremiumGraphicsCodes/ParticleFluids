#ifndef __CRYSTAL_SHAPE_POLYGON_MESH_H__
#define __CRYSTAL_SHAPE_POLYGON_MESH_H__

#include "../Util/UnCopyable.h"
#include "Vertex.h"
#include "Face.h"
#include "../Math/Quaternion.h"
#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"

#include "IShape.h"

#include <list>

namespace Crystal {
	namespace Shape {

class Vertex;
class Face;

class PolygonMesh : public IShape
{
public:
	PolygonMesh()
	{}

	PolygonMesh(const std::vector<Vertex*>& vertices, const std::list<Face*>& faces);

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

	PolygonMesh* clone();

	HalfEdge* getShortestEdge();

	void mergeDouble(PolygonMesh* rhs, float distance);

	Math::Vector3df getCenter() const;

	void move(const Math::Vector3dd& v) override;

	void transform(const Math::Matrix3dd& m) override;

	void transform(const Math::Matrix4dd& m) override;

	//void scale(const Math::Vector3df& s);

	//void rotate(const Math::Quaternion<float>& quaternion);

	void merge(PolygonMesh& rhs);

	//void reverse();

	std::list<Vertex*> findInnerVertices();

	std::list<Vertex*> findBoundaryVertices();

	std::list<HalfEdge*> findBoundaryEdges();

	void updateNormals();

private:
	std::vector<Vertex*> vertices;
	std::list<Face*> faces;
};

	}
}

#endif