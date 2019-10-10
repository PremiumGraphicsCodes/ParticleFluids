#pragma once

#include "IWindow.h"

#include "IntView.h"
#include "Vector3dView.h"
#include "Vector2dView.h"
#include "StringView.h"

namespace Crystal {
	namespace Scene {
		class Vertex;
	}
	namespace UI {

class VertexView : public IWindow
{
public:
	explicit VertexView(const std::string& name);

	VertexView(const std::string& name, Scene::Vertex* value);

	void onShow() override;

	void setValue(Scene::Vertex* value);

private:
	IntView id;
	Vector3dView position;
	Vector3dView normal;
	Vector2dView texCoord;
	Scene::Vertex* value;
};

	}
}