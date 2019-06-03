#pragma once

#include "IWindow.h"
#include "imgui.h"

#include "IntView.h"
#include "Vector3dView.h"
#include "Vector2dView.h"
#include "StringView.h"

namespace Crystal {
	namespace Shape {
		class Vertex;
	}
	namespace UI {

class PolygonVertexView : public IWindow
{
public:
	explicit PolygonVertexView(const std::string& name);

	PolygonVertexView(const std::string& name, Shape::Vertex* value);

	void show() override;

	void setValue(Shape::Vertex* value);

private:
	IntView id;
	Vector3dView position;
	Vector3dView normal;
	Vector2dView texCoord;
	Shape::Vertex* value;
};

	}
}