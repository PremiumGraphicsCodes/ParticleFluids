#pragma once

#include "IScene.h"
#include "../Shape/Face.h"

namespace Crystal {
	namespace Scene {

class FaceGroupScene : public IScene
{
public:
	FaceGroupScene(const int id, const std::string& name);

	void addFace(Shape::Face f) { this->faces.push_back(f); }

	std::vector<Shape::Face> getFaces() const { return faces; }

	void setMaterialName(const std::string& name);

	std::string getMaterialName() const { return materialName; }

	SceneType getType() const override { return SceneType::FaceGroupScene; }

	void toViewModel(SceneViewModel& viewModel) const;

	//void toIdViewModel(SceneIdViewModel& parentIdViewModel, SceneIdViewModel& childIdViewModel) const;

	void onClear() override {
		faces.clear();
	}

private:
	std::string materialName;
	int materialId;
	int ambientTextureId;
	std::vector<Shape::Face> faces;

};

	}
}