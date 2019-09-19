#pragma once

#include "IWindow.h"
#include "imgui.h"

#include "IntView.h"
#include "StringView.h"
#include "VertexView.h"

namespace Crystal {
	namespace Scene {
		class Face;
	}
	namespace UI {

class FaceView : public IWindow
{
public:
	explicit FaceView(const std::string& name);

	FaceView(const std::string& name, Scene::Face* value);

	void onShow() override;

	void setValue(Scene::Face* value);

	Scene::Face* getValue() const { return value; }

private:
	IntView id;
	IntView vertex1;
	IntView vertex2;
	IntView vertex3;
	Scene::Face* value;
};
	}
}