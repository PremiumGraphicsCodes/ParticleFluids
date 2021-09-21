#include "TriangleMeshScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;

TriangleMeshScene::TriangleMeshScene(const int id)
	: IShapeScene(id)
{
//	presenter = std::make_unique
}

TriangleMeshScene::TriangleMeshScene(const int id, const std::string& name, std::unique_ptr<Shape::TriangleMesh> shape) :
	IShapeScene(id, name),
	shape(std::move(shape))
{}


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