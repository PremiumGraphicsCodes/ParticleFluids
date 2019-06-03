#pragma once

#include "IWindow.h"
#include "imgui.h"

#include "IntView.h"
#include "StringView.h"

namespace Crystal {
	namespace Shape {
		class Face;
	}
	namespace UI {

class PolygonFaceView : public IWindow
{
public:
	PolygonFaceView(const std::string& name, Shape::Face* face);

	void show() override;

private:
	StringView name;
	IntView id;
	Shape::Face* face;
};

	}
}