#pragma once

#include "IEditCancelView.h"
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

class FaceGroupEditView : public IEditCancelView
{
public:
	FaceGroupEditView(const std::string& name, Scene::World* world, Canvas* canvas);

	void setValue(Scene::FaceGroupScene* value);

private:
	void onEdit();

private:
	IntView idView;
	StringView nameView;
	StringView materialNameView;
};

	}
}
