#pragma once

#include "IWindow.h"
#include "PolygonMeshView.h"
#include "IntView.h"
#include "StringView.h"
#include "Button.h"
#include "../Scene/PolygonMeshScene.h"
#include "../Scene/RootScene.h"
#include "../UI/Canvas.h"

namespace Crystal {
	namespace UI {

class PolygonMeshEditView : public IWindow
{
public:
	PolygonMeshEditView(const std::string& name, Scene::RootScene* repository, Canvas* canvas);

	void show() override;

	void setValue(Scene::PolygonMeshScene* value);

private:
	void onEdit();

private:
	PolygonMeshView polygonMesh;
	IntView id;
	StringView name;
	StringView materialName;
	Button edit;
};

	}
}
