#include "TriangleFace.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;

TriangleFace::TriangleFace(const std::array<Vector3dd, 3>& vertices) :
	vertices(vertices)
{
	this->normal = toTriangle().getNormal();
}

void TriangleFace::translate(const Vector3dd& vec)
{
	for (auto& v : vertices) {
		v += vec;
	}
}

void TriangleFace::transform(const Matrix3dd& m)
{
	for (auto& v : vertices) {
		v  = v * m;
	}
}

void TriangleFace::transform(const Matrix4dd& m)
{
	for (auto& v : vertices) {
		v = glm::vec4(v,1.0) * m;
	}
}
