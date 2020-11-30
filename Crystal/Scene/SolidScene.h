#pragma once

#include "IShapeScene.h"
#include "../Shape/Solid.h"
#include "../Graphics/ColorRGBA.h"
#include "SolidAsWFPresenter.h"

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

	IPresenter* getPresenter() override { return presenter.get(); }

	void setColor(const Graphics::ColorRGBAf& color) { this->color = color; }

	Graphics::ColorRGBAf getColor() const { return color; }

	Math::Box3d getBoundingBox() const { return shape->getBoundingBox(); }

private:
	std::unique_ptr<Shape::Solid> shape;
	std::unique_ptr<SolidAsWFPresenter> presenter;
	Graphics::ColorRGBAf color;
};

	}
}