#pragma once

#include "IShapeScene.h"
#include "../Shape/TriangleMesh.h"

namespace Crystal {
	namespace Scene {

class TriangleMeshScene : public IShapeScene
{
public:
	explicit TriangleMeshScene(const int id)
		: IShapeScene(id, nullptr)
	{}

	TriangleMeshScene(const int id, const std::string& name, std::unique_ptr<Shape::TriangleMesh> shape) :
		IShapeScene(id, name, shape.get()),
		shape(std::move(shape))
	{}

	void translate(const Math::Vector3dd& v) override;

	void transform(const Math::Matrix3dd& m) override;

	void transform(const Math::Matrix4dd& m) override;

	Math::Vector3dd getPosition(const int index) const override;

	std::vector<Math::Vector3dd> getAllVertices() const { return {}; }

	void send(ScreenIdShaderBuffer& parentIdViewModel, ScreenIdShaderBuffer& childIdViewModel) const override {}

	IShapeScene* clone() const override { return nullptr; }

	SceneType getType() const override { return SceneType::TriangleMeshScene; }

private:
	std::unique_ptr<Shape::TriangleMesh> shape;
};

	}
}