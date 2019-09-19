#pragma once

#include "IWindow.h"
#include "imgui.h"

#include "IntView.h"

namespace Crystal {
	namespace Scene {
		class PolygonMesh;
	}
	namespace UI {

class PolygonMeshView : public IWindow
{
public:
	explicit PolygonMeshView(const std::string& name);

	void onShow() override;

	void setValue(Scene::PolygonMesh* value);

private:
	IntView vertexCount;
	IntView faceCount;
};

	}
}