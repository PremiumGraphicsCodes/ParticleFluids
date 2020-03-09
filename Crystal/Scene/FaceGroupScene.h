#pragma once

#include "IScene.h"
#include "../Shape/Face.h"

namespace Crystal {
	namespace Scene {
		class PolygonMeshScene;
		class MaterialScene;

class FaceGroupScene : public IScene
{
public:
	FaceGroupScene(const int id, const std::string& name, PolygonMeshScene* polygonMesh);

	void addFace(Shape::Face f) { this->faces.push_back(f); }

	std::vector<Shape::Face> getFaces() const { return faces; }

	void setMaterial(MaterialScene* material);

	MaterialScene* getMaterial() const { return material; }

	SceneType getType() const override { return SceneType::FaceGroupScene; }

	void send(SceneViewModel& viewModel) const;

	//void toIdViewModel(SceneIdViewModel& parentIdViewModel, SceneIdViewModel& childIdViewModel) const;

	void onClear() override {
		faces.clear();
	}

private:
	PolygonMeshScene* polygonMesh;
	MaterialScene* material;
	std::vector<Shape::Face> faces;

};

	}
}