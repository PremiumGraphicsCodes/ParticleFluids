#pragma once

#include "IScene.h"
#include "../Shape/Face.h"

namespace Crystal {
	namespace Scene {

class FaceGroupScene : public IScene
{
public:
	FaceGroupScene(const int id, const std::string& name) :
		IScene(id, name)
	{}

	void addFace(Shape::Face f) { this->faces.push_back(f); }

	std::vector<Shape::Face> getFaces() const { return faces; }

	//int getId() const { return id; }

	void setMaterialName(const std::string& name) { this->materialName = name; }

	std::string getMaterialName() const { return materialName; }

	SceneType getType() const override { return SceneType::FaceGroupScene; }

	void toViewModel(SceneViewModel& viewModel) const;

	void onClear() override {
		faces.clear();
	}

private:
	std::string materialName;
	std::vector<Shape::Face> faces;

};

	}
}