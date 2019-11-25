#pragma once

#include "IWindow.h"

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

	void onShow() override;

	void setValue(Shape::PolygonMesh* value);

private:
	IntView vertexCount;
	IntView faceCount;
};

	}
}