#include "TriangleMeshScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;

void TriangleMeshScene::translate(const Vector3dd& v)
{
	for (auto& f : faces) {
		f.translate(v);
	}
}

void TriangleMeshScene::transform(const Matrix3dd& m)
{
	for (auto& f : faces) {
		f.transform(m);
	}
}

void TriangleMeshScene::transform(const Matrix4dd& m)
{
	for (auto& f : faces) {
		f.transform(m);
	}
}

Vector3dd TriangleMeshScene::getPosition(const int index) const
{
	assert(false);
	return Vector3dd();
}
