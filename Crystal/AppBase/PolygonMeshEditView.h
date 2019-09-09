#pragma once

#include "IWindow.h"
#include "PolygonMeshView.h"
#include "IntView.h"
#include "StringView.h"
#include "Button.h"
#include "../Scene/PolygonMeshScene.h"
#include "../Scene/World.h"
#include "Canvas.h"

namespace Crystal {
	namespace UI {

class PolygonMeshEditView : public IWindow
{
public:
	PolygonMeshEditView(const std::string& name, Scene::World* repository, Canvas* canvas);

	void onShow() override;

	void setValue(Scene::PolygonMeshScene* value);

private:
	void onEdit();

private:
	PolygonMeshView polygonMesh;
	Scene::World* world;
	IntView id;
	StringView name;
	Button edit;
};

	}
}
