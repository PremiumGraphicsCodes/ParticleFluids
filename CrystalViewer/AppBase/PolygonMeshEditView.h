#pragma once

#include "IView.h"
#include "PolygonMeshView.h"
#include "IntView.h"
#include "StringView.h"
#include "Button.h"
#include "Canvas.h"
#include "ComboBox.h"

#include "../../Crystal/Scene/PolygonMeshScene.h"
#include "../../Crystal/Scene/World.h"

namespace Crystal {
	namespace UI {

class PolygonMeshEditView : public IView
{
public:
	PolygonMeshEditView(const std::string& name, Scene::World* repository, Canvas* canvas);

	void setValue(Scene::PolygonMeshScene* value);

private:
	void onEdit();

private:
	PolygonMeshView polygonMeshView;
	Scene::World* world;
	IntView idView;
	StringView nameView;
	Button editButton;

};

	}
}
