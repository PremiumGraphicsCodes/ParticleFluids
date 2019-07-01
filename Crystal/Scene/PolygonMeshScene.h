#pragma once

#include "IShapeScene.h"
#include "../Shape/PolygonMesh.h"
#include "../Graphics/ColorRGBA.h"
#include "MaterialScene.h"

namespace Crystal {
	namespace Model {

class PolygonMeshScene : public IShapeScene
{
public:
	PolygonMeshScene() :
		IShapeScene(-1),
		shape(nullptr),
		material(nullptr)
	{}

	PolygonMeshScene(const int id, const std::string& name, Shape::PolygonMesh* shape, MaterialScene* material) :
		IShapeScene(id, name),
		shape(shape),
		material(material)
	{}

	~PolygonMeshScene() {};

	Shape::PolygonMesh* getShape() const { return shape; }

	void move(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) { shape->transform(m); }

	bool isNull() const override { return shape == nullptr; }

	SceneType getType() const override { return SceneType::PolygonMeshScene; }

	void onClear() override
	{
		delete shape;
	}

	const MaterialScene* getMaterial() const { return material; }

	virtual void addViewModel(UI::SceneViewModel& viewModel) override;

	virtual void addViewModel(UI::SceneIdViewModel& viewModel) override;

	virtual void getBoundingBox(Math::Box3d& boundingBox) const override;

private:
	Shape::PolygonMesh* shape;
	MaterialScene* material;

};

	}
}