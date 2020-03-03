#include "TriangleMesh.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

TriangleMesh::TriangleMesh()
{
}

TriangleMesh::~TriangleMesh()
{
}

void TriangleMesh::clear()
{
	faces.clear();
}

Vector3dd TriangleMesh::getCenter() const
{
	return getBoundingBox().getCenter();
}

void TriangleMesh::move(const Vector3dd& v)
{
	for (auto& f : faces) {
		f.triangle.translate(v);
	}
}

void TriangleMesh::transform(const Matrix3dd& m)
{
	for (auto& f : faces) {
		f.triangle.transform(m);
	}
}

void TriangleMesh::transform(const Matrix4dd& m)
{
	for (auto& f : faces) {
		f.triangle.transform(m);
	}
}

Box3d TriangleMesh::getBoundingBox() const
{
	auto bb = faces.front().triangle.getBoundingBox();
	for (auto& f : faces) {
		bb.add( f.triangle.getBoundingBox() );
	}
	return bb;
}

void TriangleMesh::addFace(const TriangleFace& face)
{
	this->faces.push_back(face);
}
