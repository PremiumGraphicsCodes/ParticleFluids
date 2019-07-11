#pragma once

#include "IShapeScene.h"
#include "../Shape/PolygonMesh.h"
#include "../Graphics/ColorRGBA.h"
#include "MaterialScene.h"

namespace Crystal {
	namespace Scene {

class FaceGroupScene : public IShapeScene
{
public:
	FaceGroupScene() :
		IShapeScene(-1)
	{}

	FaceGroupScene(const int id, const std::string& name, const std::list<Shape::Face>& faces) :
		IShapeScene(id, name),
		faces(faces)
	{}

	~FaceGroupScene() {};

	std::list<Shape::Face> getShape() const { return faces; }

	void move(const Math::Vector3dd& v) override { ; }

	void transform(const Math::Matrix3dd& m) { ; }

	void transform(const Math::Matrix4dd& m) { ; }

	bool isNull() const override { return faces.empty(); }

	SceneType getType() const override { return SceneType::FaceGroupScene; }

	void onClear() override
	{
		faces.clear();
	}

	virtual void addViewModel(SceneViewModel& viewModel) const override;

	virtual void addViewModel(SceneIdViewModel& viewModel) const override {}

	virtual void getBoundingBox(Math::Box3d& boundingBox) const override {}

private:
	std::list<Shape::Face> faces;
	int materialId;
};

	}
}