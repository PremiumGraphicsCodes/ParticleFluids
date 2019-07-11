#pragma once

#include "../Util/UnCopyable.h"
#include "Vertex.h"
#include "VertexFactory.h"
#include "FaceGroup.h"
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

	std::list<FaceGroup> getGroups() const { return faceGroups; }

	std::vector<Vertex*> getVertices() const;

	void clear();

	bool has(Vertex* v);

	Math::Vector3dd getCenter() const;

	void move(const Math::Vector3dd& v) override;

	void transform(const Math::Matrix3dd& m) override;

	void transform(const Math::Matrix4dd& m) override;

	//Face* findFaceById(const int id);

	Math::Box3d getBoundingBox() const override;

	VertexFactory* getVertexFactory() { return &vertices; }

	void addFaceGroup(FaceGroup group) { this->faceGroups.push_back(group); }

private:
	VertexFactory vertices;
	std::list<FaceGroup> faceGroups;

};

	}
}