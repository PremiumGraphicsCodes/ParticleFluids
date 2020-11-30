#pragma once

#include "IShapeScene.h"
#include "../Shape/Solid.h"

namespace Crystal {
	namespace Scene {

class SolidScene : public IShapeScene
{
public:
	SolidScene();

	SolidScene(const int id, const std::string& name, std::unique_ptr<Shape::Solid> shape);

	void translate(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) override { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) override { shape->transform(m); }

	SceneType getType() const override { return SceneType::CSGScene; }

private:
	std::unique_ptr<Shape::Solid> shape;
};

	}
}