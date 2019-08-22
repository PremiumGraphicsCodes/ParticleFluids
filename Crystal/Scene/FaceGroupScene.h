#pragma once

#include "IScene.h"
#include "../Shape/Face.h"

namespace Crystal {
	namespace Scene {

class FaceGroupScene : public IScene
{
public:
	FaceGroupScene() :
		IScene(-1)
	{}

	void addFace(Shape::Face f) { this->faces.push_back(f); }

	std::vector<Shape::Face> getFaces() const { return faces; }

	int getId() const { return id; }

	int getMaterialId() const { return materialId; }

	SceneType getType() const override { return SceneType::FaceGroupScene; }

private:
	int id;
	int materialId;
	std::vector<Shape::Face> faces;

};

	}
}