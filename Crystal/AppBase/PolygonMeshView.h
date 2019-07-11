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
	PolygonMeshView(const std::string& name, Shape::PolygonMesh* mesh);

	void show() override;

private:
	StringView name;
	IntView vertexCount;
	IntView faceCount;
	Shape::PolygonMesh* value;
};

	}
}