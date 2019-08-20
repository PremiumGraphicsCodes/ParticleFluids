#pragma once

#include "IShapeScene.h"
#include "WireFrameAttribute.h"
#include "../Shape/WireFrame.h"

namespace Crystal {
	namespace Scene {

class WireFrameScene : public IShapeScene
{
public:
	WireFrameScene() :
		IShapeScene(-1),
		shape(nullptr)
	{}

	WireFrameScene(const int id, const std::string& name, Shape::WireFrame* shape, const WireFrameAttribute& attribute) :
		IShapeScene(id, name),
		shape(shape),
		attribute(attribute)
	{}

	~WireFrameScene() {};

	Shape::WireFrame* getShape() const { return shape; }

	WireFrameAttribute getAttribute() const { return attribute; }

	void translate(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) { shape->transform(m); }

	SceneType getType() const override { return SceneType::WireFrameScene; }

	void onClear() override { delete shape; }

	Math::Box3d getBoundingBox() const { return shape->getBoundingBox(); }

	std::vector<Math::Vector3dd> getAllVertices() const { return shape->getVertices(); }

	void toViewModel(SceneViewModel& viewModel) const override;

	SceneIdViewModel toIdViewModel() const override;

	virtual void getBoundingBox(Math::Box3d& box) const;

	Math::Vector3dd getPosition(const int index) const override;

private:
	Shape::WireFrame* shape;
	WireFrameAttribute attribute;
};

	}
}