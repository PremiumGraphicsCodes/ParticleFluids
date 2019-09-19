#pragma once

#include "IScene.h"
#include "../Scene/Face.h"

namespace Crystal {
	namespace Scene {

class FaceGroupScene : public IScene
{
public:
	FaceGroupScene(const int id, const std::string& name) :
		IScene(id, name)
	{}

	void addFace(Face f) { this->faces.push_back(f); }

	std::vector<Face> getFaces() const { return faces; }

	//int getId() const { return id; }

	void setMaterialName(const std::string& name) { this->materialName = name; }

	std::string getMaterialName() const { return materialName; }

	SceneType getType() const override { return SceneType::FaceGroupScene; }

	void toViewModel(SceneViewModel& viewModel) const;

	void toIdViewModel(SceneIdViewModel& viewModel) const override {}

	void onClear() override {
		faces.clear();
	}

private:
	std::string materialName;
	std::vector<Face> faces;

};

	}
}