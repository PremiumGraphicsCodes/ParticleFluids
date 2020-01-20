#pragma once

#include "IWindow.h"
#include "PolygonMeshView.h"
#include "IntView.h"
#include "StringView.h"
#include "Button.h"
#include "Canvas.h"
#include "MaterialView.h"

namespace Crystal {
	namespace Scene {
		class World;
		class FaceGroupScene;
	}
	namespace UI {

class FaceGroupEditView : public IWindow
{
public:
	FaceGroupEditView(const std::string& name, Scene::World* world, Canvas* canvas);

	void onShow() override;

	void setValue(Scene::FaceGroupScene* value);

private:
	void onEdit();

private:
	Scene::World* world;
	IntView id;
	StringView name;
	StringView materialName;
	Button edit;
};

	}
}
