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
	PolygonMesh()
	{}

	~PolygonMesh();

	std::vector<Vertex*> getVertices() const;

	std::vector<Face> getFaces() const { return faces; }

	void clear();

	bool has(Vertex* v);

	Math::Vector3dd getCenter() const;

	void move(const Math::Vector3dd& v) override;

	void transform(const Math::Matrix3dd& m) override;

	void transform(const Math::Matrix4dd& m) override;

	//Face* findFaceById(const int id);

	Math::Box3d getBoundingBox() const override;

	VertexFactory* getVertexFactory() { return &vertices; }

	void addFace(const Face& face) { this->faces.push_back(face); }

private:
	VertexFactory vertices;
	std::vector<Face> faces;

};

	}
}