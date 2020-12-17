
#pragma once

#include "IShapeScene.h"
#include "MaterialScene.h"
#include "IPolygonMeshPresenter.h"

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

	void setShape(std::unique_ptr<Shape::PolygonMesh> shape) {
		this->shape = std::move(shape);
	}

	void translate(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) { shape->transform(m); }

	SceneType getType() const override { return SceneType::PolygonMeshScene; }

	Math::Box3d getBoundingBox() const override;

	IPresenter* getPresenter() override { return presenter.get(); }

	void setPresenter(std::unique_ptr<IPolygonMeshPresenter> presenter) { this->presenter = std::move(presenter); }

private:
	std::unique_ptr<Shape::PolygonMesh> shape;
	std::unique_ptr<IPolygonMeshPresenter> presenter;
};

	}
}