#pragma once

#include "IShapeScene.h"
#include "MaterialScene.h"
#include "FaceGroupScene.h"

#include "../Shape/PolygonMesh.h"
#include "../Graphics/ColorRGBA.h"

namespace Crystal {
	namespace Scene {

class PolygonMeshScene : public IShapeScene
{
public:
	PolygonMeshScene();

	PolygonMeshScene(const int id, const std::string& name, std::unique_ptr<Shape::PolygonMesh> shape);

	~PolygonMeshScene() {};

	Shape::PolygonMesh* getShape() const { return shape.get(); }

	void translate(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) { shape->transform(m); }

	SceneType getType() const override { return SceneType::PolygonMeshScene; }

	void onClear() override{}

	void toViewModel(SceneViewModel& viewModel) const override;

	void toIdViewModel(SceneIdViewModel& parentIdViewModel, SceneIdViewModel& childIdViewModel) const override;

	Math::Box3d getBoundingBox() const override;

	Math::Vector3dd getPosition(const int index) const override;

	void addGroup(FaceGroupScene* group) {
		groups.push_back(group);
		addScene(group);
//		children.push_back(group);
	}

	IShapeScene* clone() const override;

private:
	std::unique_ptr<Shape::PolygonMesh> shape;
	std::vector<FaceGroupScene*> groups;
};

	}
}