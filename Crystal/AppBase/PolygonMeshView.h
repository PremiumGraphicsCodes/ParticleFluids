#pragma once

#include "IWindow.h"
#include "imgui.h"

#include "IntView.h"

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
	IntView vertexCount;
	IntView faceCount;
};

	}
}