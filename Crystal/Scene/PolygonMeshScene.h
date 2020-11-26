
#pragma once

#include "IShapeScene.h"
#include "MaterialScene.h"
#include "FaceGroupScene.h"
#include "PolygonMeshPresenter.h"

#include "../Shape/PolygonMesh.h"
#include "../Graphics/ColorRGBA.h"

namespace Crystal {
	namespace Scene {

class PolygonMeshScene : public IShapeScene
{
public:
	PolygonMeshScene();

	PolygonMeshScene(const int id, const std::string& name, std::unique_ptr<Shape::PolygonMesh> shape);

	~PolygonMeshScene();

	Shape::PolygonMesh* getShape() const { return shape.get(); }

	void translate(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) { shape->transform(m); }

	SceneType getType() const override { return SceneType::PolygonMeshScene; }

	Math::Box3d getBoundingBox() const override;

	void addGroup(FaceGroupScene* group) {
		groups.push_back(group);
		//addScene(group);
//		children.push_back(group);
	}

	std::vector<FaceGroupScene*> getGroups() { return groups; }

	IPresenter* getPresenter() override { return &controller; }

private:
	std::unique_ptr<Shape::PolygonMesh> shape;
	std::vector<FaceGroupScene*> groups;
	PolygonMeshPresenter controller;
};

	}
}