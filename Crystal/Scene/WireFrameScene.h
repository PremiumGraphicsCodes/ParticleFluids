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
	WireFrameScene();

	WireFrameScene(const int id, const std::string& name, std::unique_ptr<Shape::WireFrame> shape, const WireFrameAttribute& attribute);

	~WireFrameScene() {};

	WireFrameAttribute getAttribute() const { return attribute; }

	void translate(const Math::Vector3dd& v) override;

	void transform(const Math::Matrix3dd& m) override;

	void transform(const Math::Matrix4dd& m) override;

	SceneType getType() const override { return SceneType::WireFrameScene; }

	void onClear() override {}

	Math::Box3d getBoundingBox() const override;

	std::vector<Math::Vector3dd> getAllVertices() const;

	void toViewModel(SceneViewModel& viewModel) const override;

	void toIdViewModel(SceneIdViewModel& parentIdViewModel, SceneIdViewModel& childIdViewModel) const override;

	Math::Vector3dd getPosition(const int index) const override;

	IShapeScene* clone() const override;

private:
	std::unique_ptr<Shape::WireFrame> shape;
	WireFrameAttribute attribute;
};

	}
}