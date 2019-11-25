#pragma once

#include "IShapeScene.h"
#include "WireFrameAttribute.h"

#include "../Math/Line3d.h"
#include "../Shape/WireFrame.h"

namespace Crystal {
	namespace Scene {


class WireFrameScene : public IShapeScene
{
public:
	WireFrameScene() :
		IShapeScene(-1)
	{}

	WireFrameScene(const int id, const std::string& name, Shape::WireFrame* shape, const WireFrameAttribute& attribute) :
		IShapeScene(id, name),
		shape(shape),
		attribute(attribute)
	{}

	~WireFrameScene() {};

	WireFrameAttribute getAttribute() const { return attribute; }

	void translate(const Math::Vector3dd& v) override;

	void transform(const Math::Matrix3dd& m) override;

	void transform(const Math::Matrix4dd& m) override;

	SceneType getType() const override { return SceneType::WireFrameScene; }

	void onClear() override {
		delete shape;
	}

	//Math::Box3d getBoundingBox() const;

	//void getBoundingBox(Math::Box3d& box) const override;

	virtual void getBoundingBox(Math::Box3d& box) const override;

	std::vector<Math::Vector3dd> getAllVertices() const;

	void toViewModel(SceneViewModel& viewModel) const override;

	void toIdViewModel(SceneIdViewModel& viewModel) const override;

	Math::Vector3dd getPosition(const int index) const override;

	IShapeScene* clone() const override;

private:
	Shape::WireFrame* shape;
	WireFrameAttribute attribute;
};

	}
}