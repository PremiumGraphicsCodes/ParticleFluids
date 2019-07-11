#pragma once

#include "IWindow.h"
#include "imgui.h"

#include "IntView.h"
#include "StringView.h"
#include "FaceView.h"

#include "../Scene/FaceGroupScene.h"

namespace Crystal {
	namespace UI {

class FaceGroupView : public IWindow
{
public:
	explicit FaceGroupView(const std::string& name);

	FaceGroupView(const std::string& name, Scene::FaceGroupScene* value);

	void show() override;

	void setValue(Scene::FaceGroupScene* value);

	//Shape::FaceGroup getValue() const { return value; }

private:
	IntView id;
	IntView faceCount;
	StringView materialName;
	Scene::FaceGroupScene* value;
};

	}
}