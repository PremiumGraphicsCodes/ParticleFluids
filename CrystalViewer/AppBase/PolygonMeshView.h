#pragma once

#include "IView.h"

#include "IntView.h"
#include "ComboBox.h"

namespace Crystal {
	namespace Shape {
		class PolygonMesh;
	}
	namespace UI {

class PolygonMeshView : public IView
{
public:
	explicit PolygonMeshView(const std::string& name);

	void setValue(Shape::PolygonMesh* value);

	std::string getPresenterName() const { return presenterView.getSelected(); }

private:
	IntView vertexCount;
	IntView faceCount;
	ComboBox presenterView;
};

	}
}