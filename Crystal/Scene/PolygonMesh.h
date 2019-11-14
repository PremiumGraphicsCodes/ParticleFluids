#pragma once

#include "../Util/UnCopyable.h"
#include "../Math/Quaternion.h"
#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"
#include "../Math/Triangle3d.h"
#include "../Math/Line3d.h"

#include "Vertex.h"
#include "Face.h"

#include "IShape.h"

#include <list>

namespace Crystal {
	namespace Scene {

class Vertex;
class Face;

class PolygonMesh : public IShape
{
public:
	PolygonMesh();

	~PolygonMesh();

	std::vector<Vertex> getVertices() const;

	std::vector<Face> getFaces() const { return faces; }

	void clear();

	Math::Vector3dd getCenter() const;

	void move(const Math::Vector3dd& v) override;

	void transform(const Math::Matrix3dd& m) override;

	void transform(const Math::Matrix4dd& m) override;

	//Face* findFaceById(const int id);

	Math::Box3d getBoundingBox() const override;

	std::vector<Math::Vector3dd> getPositions() const { return positions; }

	std::vector<Math::Vector3dd> getNormals() const { return normals; }

	std::vector<Math::Vector2dd> getTexCoords() const { return texCoords; }

public:
	std::vector<Math::Vector3dd> positions;
	std::vector<Math::Vector3dd> normals;
	std::vector<Math::Vector2dd> texCoords;
	std::vector<Vertex> vertices;
	std::vector<Face> faces;
};

	}
}