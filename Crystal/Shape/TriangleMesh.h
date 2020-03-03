#pragma once

#include "../Shape/IShape.h"
#include "../Math/Triangle3d.h"

#include <vector>

namespace Crystal {
	namespace Shape {

class TriangleFace
{
public:
	Math::Vector3dd normal;
	Math::Triangle3d triangle;
};

class TriangleMesh : public IShape
{
public:
	TriangleMesh();

	~TriangleMesh();

	void clear();

	Math::Vector3dd getCenter() const;

	void move(const Math::Vector3dd& v) override;

	void transform(const Math::Matrix3dd& m) override;

	void transform(const Math::Matrix4dd& m) override;

	//Face* findFaceById(const int id);

	Math::Box3d getBoundingBox() const override;

	std::vector<TriangleFace> getFaces() const { return faces; }

	void addFace(const TriangleFace& faces);

public:
	std::vector<TriangleFace> faces;
};

	}
}