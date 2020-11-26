#include "TriangleMeshScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;

void TriangleMeshScene::translate(const Vector3dd& v)
{
	shape->move(v);
}

void TriangleMeshScene::transform(const Matrix3dd& m)
{
	shape->transform(m);
}

void TriangleMeshScene::transform(const Matrix4dd& m)
{
	shape->transform(m);
}