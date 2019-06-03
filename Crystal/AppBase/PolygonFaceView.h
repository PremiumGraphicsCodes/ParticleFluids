#pragma once

#include "IWindow.h"
#include "imgui.h"

#include "IntView.h"
#include "StringView.h"
#include "PolygonVertexView.h"

namespace Crystal {
	namespace Shape {
		class Face;
	}
	namespace UI {

class PolygonFaceView : public IWindow
{
public:
	explicit PolygonFaceView(const std::string& name);

	PolygonFaceView(const std::string& name, Shape::Face* value);

	void show() override;

	void setValue(Shape::Face* value);

	Shape::Face* getValue() const { return value; }

private:
	IntView id;
	Shape::Face* value;
	PolygonVertexView vertex1;
	PolygonVertexView vertex2;
	PolygonVertexView vertex3;
};

	}
}