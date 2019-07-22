#pragma once

#include "IWindow.h"
#include "imgui.h"

#include "IntView.h"
#include "StringView.h"

namespace Crystal {
	namespace Shape {
		class PolygonMesh;
	}
	namespace UI {

class PolygonMeshView : public IWindow
{
public:
	explicit PolygonMeshView(const std::string& name);

	void show() override;

	void setValue(Shape::PolygonMesh* value);

private:
	StringView name;
	IntView vertexCount;
	IntView faceCount;
};

	}
}