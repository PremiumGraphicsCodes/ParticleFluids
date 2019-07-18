#pragma once

#include "IShapeScene.h"
#include "../Shape/PolygonMesh.h"
#include "../Graphics/ColorRGBA.h"
#include "MaterialScene.h"

namespace Crystal {
	namespace Scene {

class FaceGroupScene : public IScene
{
public:
	FaceGroupScene() :
		IScene(-1)
	{}

	FaceGroupScene(const int id, const std::string& name, const std::vector<Shape::Face>& faces) :
		IScene(id, name),
		faces(faces)
	{}

	~FaceGroupScene() {};

	std::vector<Shape::Face> getShape() const { return faces; }

	//void move(const Math::Vector3dd& v) override { ; }

	//void transform(const Math::Matrix3dd& m) override { ; }

	//void transform(const Math::Matrix4dd& m) override { ; }

	void addFace(const Shape::Face& f) { faces.push_back(f); }

	void setMaterialName(const std::string& mname) { this->materialName = mname; }

	SceneType getType() const override { return SceneType::FaceGroupScene; }

	void onClear() override
	{
		faces.clear();
	}

	virtual void addViewModel(SceneViewModel& viewModel) const override;

	virtual void addViewModel(SceneIdViewModel& viewModel) const override {}

	virtual void getBoundingBox(Math::Box3d& boundingBox) const override {}

	std::string getMaterialName() const { return materialName; }

private:
	std::vector<Shape::Face> faces;
	std::string materialName;
};

	}
}