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
	PolygonMeshScene() :
		IShapeScene(-1, nullptr),
		shape(nullptr)
	{}

	PolygonMeshScene(const int id, const std::string& name, Shape::PolygonMesh* shape) :
		IShapeScene(id, name, shape),
		shape(shape)
	{}

	~PolygonMeshScene() {};

	Shape::PolygonMesh* getShape() const { return shape; }

	void translate(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) { shape->transform(m); }

	SceneType getType() const override { return SceneType::PolygonMeshScene; }

	void onClear() override
	{
		delete shape;
	}

	void toViewModel(SceneViewModel& viewModel) const override;

	void toIdViewModel(SceneIdViewModel& parentIdViewModel, SceneIdViewModel& childIdViewModel) const override;

	void getBoundingBox(Math::Box3d& boundingBox) const override;

	Math::Vector3dd getPosition(const int index) const override;

	void addGroup(FaceGroupScene* group) {
		groups.push_back(group);
		children.push_back(group);
	}

	IShapeScene* clone() const override;

private:
	Shape::PolygonMesh* shape;
	std::vector<FaceGroupScene*> groups;
};

	}
}